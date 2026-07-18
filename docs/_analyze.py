#!/usr/bin/env python3
# Repository analysis helper.
# Read-only: enumerates files, computes hashes, detects duplicate/versioned
# filenames, and emits inventory.csv plus two markdown reports.
import csv
import hashlib
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DOCS = ROOT / "docs"

# Directories we should skip when walking (the user only cares about templates/
# and 洛谷/, but we'll still index the docx/bat/py at templates root).
SKIP_DIR_NAMES = {".git", "docs"}

# Categories that should not normally be committed to git.
BAD_EXTENSIONS = {
    ".exe", ".obj", ".o", ".out", ".class", ".jar",
    ".pdb", ".ilk", ".exp", ".lib", ".so", ".dll", ".dylib",
    ".pyc", ".pyo", ".pyd",
    ".tmp", ".temp", ".swp", ".swo", ".bak", ".backup", ".old", ".orig",
    ".log", ".cache", ".DS_Store", "Thumbs.db",
    ".aux", ".bbl", ".blg", ".toc", ".out", ".synctex.gz",
}
BAD_NAMES = {"a.out", "a.exe", "core", "core.dump", "nul", "null"}

TEXTUAL_EXTS = {
    ".cpp", ".cc", ".cxx", ".c", ".h", ".hpp", ".hh", ".hxx",
    ".py", ".java", ".kt", ".go", ".rs", ".js", ".ts",
    ".md", ".txt", ".json", ".yaml", ".yml", ".toml", ".ini",
    ".bat", ".sh", ".ps1",
    ".in", ".out", ".ans",
    ".gitattributes", ".gitignore",
}

# Regexes that detect "main()" so we can tell templates from full problem
# solutions. We intentionally look for a function definition with `main`,
# not just any occurrence of the word.
MAIN_PATTERNS = [
    re.compile(r"\bint\s+main\s*\("),
    re.compile(r"\bvoid\s+main\s*\("),
    re.compile(r"\bmain\s*\(\s*void\s*\)\s*\{"),
    re.compile(r"\bint\s+MAIN\s*\("),
]

# Filename tokens that suggest a second/alternate version of the same problem.
VERSION_TOKENS = [
    re.compile(r"[(（]\s*(\d+)\s*[)）]"),         # P1234(2) / P1234（2）
    re.compile(r"[_\-]\s*(\d+)\s*$"),            # P1234_2 / P1234-2
    re.compile(r"[_\-]\s*v(\d+)\s*$", re.IGNORECASE),
    re.compile(r"(副本|备份|backup|copy|复件)", re.IGNORECASE),
    re.compile(r"(新版|旧版|new|old|改|fix|debug)", re.IGNORECASE),
]

# Luogu problem ID detection.  Luogu problem codes look like P1234, P1000,
# AT_abc123_a, UVA123, CF1234A, SP1234, BZOJ1234, POJ1234, etc.  We also
# catch the `题目编号` pattern in the first comment block if we ever peek
# into file content (we don't, but the URL heuristic below keeps the
# inventory honest).
PROBLEM_ID_RE = re.compile(
    r"\b("
    r"P|AT_|UVA|CF|SP|BZOJ|POJ|HDU|LOJ|LibreOJ|Codeforces|SPOJ"
    r")\s*[-_]?\s*(\d{1,5})([A-Za-z](_[A-Za-z0-9]+)?)?\b"
)


def sha256_of(path: Path, blocksize: int = 1 << 16) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        while True:
            chunk = fh.read(blocksize)
            if not chunk:
                break
            h.update(chunk)
    return h.hexdigest()


def line_count(path: Path) -> int:
    try:
        with open(path, "rb") as fh:
            return sum(1 for _ in fh)
    except OSError:
        return 0


def has_main(path: Path) -> bool:
    try:
        with open(path, "rb") as fh:
            data = fh.read()
    except OSError:
        return False
    try:
        text = data.decode("utf-8")
    except UnicodeDecodeError:
        text = data.decode("gbk", errors="ignore")
    # Cheap pre-filter.
    if "main" not in text:
        return False
    return any(p.search(text) for p in MAIN_PATTERNS)


def looks_textual(path: Path) -> bool:
    return path.suffix.lower() in TEXTUAL_EXTS or path.name.lower() in TEXTUAL_EXTS


def detect_problem_id(name: str) -> str:
    m = PROBLEM_ID_RE.search(name)
    if not m:
        return ""
    prefix, num, suffix = m.group(1), m.group(2), m.group(3) or ""
    return f"{prefix}{num}{suffix}"


def detect_version_suffix(name: str):
    """Return (base, version) tuple if the filename looks like a duplicate-
    versioned copy of another file.  Otherwise return (name, None)."""
    base, dot, ext = name.partition(".")
    version = None
    for pat in VERSION_TOKENS:
        m = pat.search(base)
        if m:
            version = m.group(0)
            stripped = pat.sub("", base).rstrip(" _-")
            base = stripped or base
            break
    if version is None:
        return name, None
    return (f"{base}.{ext}" if dot else base, version)


def is_bad_for_git(path: Path) -> bool:
    if path.name in BAD_NAMES:
        return True
    if path.suffix.lower() in BAD_EXTENSIONS:
        return True
    # Heuristic for compile artifacts with no extension or odd suffixes.
    if path.suffix == "" and path.name.startswith("a."):
        return True
    return False


def relative_posix(path: Path) -> str:
    return str(path.relative_to(ROOT)).replace(os.sep, "/")


def walk_repo():
    for dirpath, dirnames, filenames in os.walk(ROOT):
        dirnames[:] = [d for d in dirnames if d not in SKIP_DIR_NAMES]
        for fn in filenames:
            yield Path(dirpath) / fn


def main():
    files = sorted(walk_repo())

    inventory_rows = []
    by_dir_count = defaultdict(int)
    by_ext_count = defaultdict(int)
    by_dir_ext = defaultdict(lambda: defaultdict(int))
    hash_to_paths = defaultdict(list)
    versioned_groups = defaultdict(list)
    templates_main_count = 0
    templates_main_files = []
    templates_total = 0
    luogu_total = 0
    bad_files = []
    template_dirs = {}
    luogu_dirs = {}

    for fp in files:
        rel = fp.relative_to(ROOT)
        rel_posix = relative_posix(fp)
        ext = fp.suffix.lower()
        size = fp.stat().st_size
        lines = line_count(fp) if looks_textual(fp) and size < 2_000_000 else 0
        sha = sha256_of(fp) if size <= 50_000_000 else ""
        if sha:
            hash_to_paths[sha].append(rel_posix)

        # has_main only meaningful for C/C++/Java/Python-like files.
        main_flag = ""
        if ext in {".cpp", ".cc", ".cxx", ".c", ".h", ".hpp", ".java", ".py", ".go", ".rs", ".kt"}:
            main_flag = "true" if has_main(fp) else "false"

        # Problem ID + URL.
        prob_id = detect_problem_id(fp.name)
        url = f"https://www.luogu.com.cn/problem/{prob_id}" if prob_id.startswith("P") and prob_id[1:].isdigit() else ""

        # Version detection.
        base, version = detect_version_suffix(fp.name)
        if version:
            versioned_groups[base].append((rel_posix, version))

        # Directory classification.
        parts = rel.parts
        is_template = parts and parts[0] == "templates"
        is_luogu = parts and parts[0] == "洛谷"
        if is_template:
            templates_total += 1
            if main_flag == "true":
                templates_main_count += 1
                templates_main_files.append(rel_posix)
            sub = parts[1] if len(parts) > 1 else "<root>"
            template_dirs.setdefault(sub, []).append(rel_posix)
        elif is_luogu:
            luogu_total += 1
            sub = parts[1] if len(parts) > 1 else "<root>"
            luogu_dirs.setdefault(sub, []).append(rel_posix)

        if is_bad_for_git(fp):
            bad_files.append((rel_posix, size, ext or "<no-ext>"))

        # Counts.
        top = parts[0] if parts else "<root>"
        by_dir_count[top] += 1
        by_ext_count[ext or "<no-ext>"] += 1
        if is_template and len(parts) > 1:
            by_dir_ext[parts[1]][ext or "<no-ext>"] += 1
        elif is_luogu:
            by_dir_ext["洛谷/" + (parts[1] if len(parts) > 1 else "<root>")][ext or "<no-ext>"] += 1
        else:
            by_dir_ext[top][ext or "<no-ext>"] += 1

        inventory_rows.append({
            "path": rel_posix,
            "filename": fp.name,
            "extension": ext.lstrip("."),
            "size_bytes": size,
            "lines": lines,
            "sha256": sha,
            "has_main": main_flag,
            "problem_url": url,
            "possible_problem_id": prob_id,
        })

    # ---------------- inventory.csv ----------------
    csv_path = DOCS / "inventory.csv"
    fields = ["path", "filename", "extension", "size_bytes", "lines",
              "sha256", "has_main", "problem_url", "possible_problem_id"]
    with open(csv_path, "w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=fields)
        w.writeheader()
        w.writerows(inventory_rows)
    print(f"Wrote {csv_path} with {len(inventory_rows)} rows")

    # ---------------- duplicate-report.md ----------------
    dup_lines = ["# 重复与疑似多版本文件报告", "",
                 f"扫描根目录：`{ROOT}`", "",
                 f"共扫描 {len(inventory_rows)} 个文件。", ""]

    dup_lines.append("## 1. SHA-256 完全一致的文件")
    real_dupes = {h: paths for h, paths in hash_to_paths.items() if len(paths) > 1}
    if not real_dupes:
        dup_lines.append("")
        dup_lines.append("- 未发现 SHA-256 完全一致的文件。")
    else:
        dup_lines.append("")
        dup_lines.append(f"共发现 {len(real_dupes)} 组重复文件。")
        dup_lines.append("")
        for h, paths in sorted(real_dupes.items(), key=lambda kv: (-len(kv[1]), kv[1][0])):
            dup_lines.append(f"### 哈希 `{h[:16]}…`")
            dup_lines.append("")
            for p in paths:
                dup_lines.append(f"- `{p}`")
            dup_lines.append("")

    dup_lines.append("## 2. 疑似同一道题的多个版本（按文件名推断）")
    dup_lines.append("")
    dup_lines.append("判定规则：文件名包含 `(2)`、`_2`、`-2`、`副本`、`备份`、`copy`、`新版/旧版` 等版本标记。")
    dup_lines.append("")
    if not versioned_groups:
        dup_lines.append("- 未检测到带版本后缀的文件。")
    else:
        dup_lines.append(f"共发现 {len(versioned_groups)} 个疑似多版本的文件名族。")
        dup_lines.append("")
        dup_lines.append("| 规范化名称 | 文件数 | 命中文件 |")
        dup_lines.append("| --- | --- | --- |")
        for base, entries in sorted(versioned_groups.items(), key=lambda kv: kv[0]):
            rows = "、".join(f"`{p}` (标记 `{v}`)" for p, v in entries)
            dup_lines.append(f"| `{base}` | {len(entries)} | {rows} |")
    dup_lines.append("")

    with open(DOCS / "duplicate-report.md", "w", encoding="utf-8") as fh:
        fh.write("\n".join(dup_lines))
    print(f"Wrote {DOCS / 'duplicate-report.md'}")

    # ---------------- repository-analysis.md ----------------
    rep = []
    rep.append("# 仓库整体结构分析")
    rep.append("")
    rep.append(f"- 仓库根目录：`{ROOT}`")
    rep.append(f"- 顶层目录：")
    rep.append("")
    rep.append("  | 顶层目录 | 文件数 |")
    rep.append("  | --- | --- |")
    for d, c in sorted(by_dir_count.items(), key=lambda kv: (-kv[1], kv[0])):
        rep.append(f"  | `{d}` | {c} |")
    rep.append("")

    rep.append("## 1. 扩展名分布")
    rep.append("")
    rep.append("| 扩展名 | 文件数 |")
    rep.append("| --- | --- |")
    for e, c in sorted(by_ext_count.items(), key=lambda kv: (-kv[1], kv[0])):
        rep.append(f"| `{e}` | {c} |")
    rep.append("")

    rep.append("## 2. `templates/` 子目录")
    rep.append("")
    rep.append("| 子目录 | 文件数 | 主要扩展名 |")
    rep.append("| --- | --- | --- |")
    for sub, paths in sorted(template_dirs.items(), key=lambda kv: (-len(kv[1]), kv[0])):
        exts = by_dir_ext.get(sub, {})
        ext_str = ", ".join(f"`{e}`={c}" for e, c in sorted(exts.items(), key=lambda kv: -kv[1])[:5]) or "-"
        rep.append(f"| `{sub}` | {len(paths)} | {ext_str} |")
    rep.append("")

    rep.append("## 3. `templates/` 中含 `main` 的文件")
    rep.append("")
    rep.append(f"- 模板目录共 **{templates_total}** 个文件，其中带 `main` 的有 **{templates_main_count}** 个。")
    rep.append("- 严格意义上的“算法模板”通常不写 `main` 也不读入整段样例。下面这些文件被识别为带 `main`，疑似是题目代码混入模板区，需要进一步人工确认：")
    rep.append("")
    if templates_main_files:
        for p in templates_main_files:
            rep.append(f"  - `{p}`")
    else:
        rep.append("  - （无）")
    rep.append("")

    rep.append("## 4. `洛谷/` 子目录")
    rep.append("")
    rep.append("| 子目录 | 文件数 | 主要扩展名 |")
    rep.append("| --- | --- | --- |")
    for sub, paths in sorted(luogu_dirs.items(), key=lambda kv: (-len(kv[1]), kv[0])):
        exts = by_dir_ext.get("洛谷/" + sub, {})
        ext_str = ", ".join(f"`{e}`={c}" for e, c in sorted(exts.items(), key=lambda kv: -kv[1])[:5]) or "-"
        rep.append(f"| `{sub}` | {len(paths)} | {ext_str} |")
    rep.append("")

    rep.append("## 5. 不应提交到 Git 的文件")
    rep.append("")
    rep.append("判断规则：扩展名属于编译产物/缓存/备份/临时文件，或文件名是常见产物名（`a.out`、`core`、`nul` 等）。")
    rep.append("")
    if bad_files:
        rep.append(f"共发现 **{len(bad_files)}** 个疑似遗留产物/临时文件。")
        rep.append("")
        rep.append("| 路径 | 大小 (字节) | 扩展名 |")
        rep.append("| --- | --- | --- |")
        for p, size, ext in sorted(bad_files):
            rep.append(f"| `{p}` | {size} | `{ext}` |")
    else:
        rep.append("- 未发现明显的产物/临时文件。")
    rep.append("")

    rep.append("## 6. `templates/` 分类规范性观察")
    rep.append("")
    rep.append("- 多数子目录以中文算法名命名（`线段树`、`网络流` 等），便于人类阅读；少数使用英文（`KMP`、`Manacher`、`AC自动机`、`CDQ分治`、`tarjan`、`twosat`、`kruskal重构树`）。")
    rep.append("- 个别目录存在轻微大小写或合并写法问题（如 `tarjan` 与 `点分治` 在不同分支、AC 自动机未使用全角空格），如需统一可在重构阶段处理。")
    rep.append("- 顶部存在非源码文件：")
    rep.append("  - `templates/code.docx`（约 1.4 MB，文档，建议确认是否仍需要）")
    rep.append("  - `templates/count.py`、`templates/count_all.bat`")
    rep.append("  - `洛谷/count_all.bat`、`洛谷/.gitattributes`、`洛谷/temp.cpp`")
    rep.append("- 这些文件不影响功能，但说明历史上有人在仓库根直接放工具脚本，后续可在重构时归类到 `scripts/`。")
    rep.append("")

    rep.append("## 7. 命名/结构观察（仅记录，不处理）")
    rep.append("")
    rep.append("- `洛谷/code/` 与 `洛谷/练习赛/` 是练习题的两条主要入口。")
    rep.append("- `洛谷/temp.cpp` 位于 `洛谷/` 顶层，命名上不属于任何一类练习题，可考虑归类为草稿或删除候选。")
    rep.append("- 模板与练习的目录层级最深约 2 级，多数文件直接落在子目录根下，重命名空间干净。")
    rep.append("- 跨平台问题：仓库中存在 `templates/count.py` 与 `洛谷/count_all.bat`、根 `count_all.bat` 等 Windows/跨平台脚本；脚本本身不参与题解逻辑，无需重写。")
    rep.append("")

    rep.append("## 8. 后续建议（仅供参考，未执行）")
    rep.append("")
    rep.append("- 在 `templates/` 子目录内补充 `README.md`，说明每类模板的用途和典型调用方式。")
    rep.append("- 对疑似混入模板目录的题目文件，可在确认后迁回 `洛谷/` 或归档到 `templates/examples/`。")
    rep.append("- 对带版本后缀的文件，建议保留一份主版本、其余归档到 `_archive/` 或在文件名中标注提交者/日期。")
    rep.append("- 若确认 `templates/code.docx` 不再需要，可在重构阶段删除（本次扫描不会删除任何文件）。")
    rep.append("")

    with open(DOCS / "repository-analysis.md", "w", encoding="utf-8") as fh:
        fh.write("\n".join(rep))
    print(f"Wrote {DOCS / 'repository-analysis.md'}")


if __name__ == "__main__":
    main()