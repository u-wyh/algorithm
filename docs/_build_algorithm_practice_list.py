#!/usr/bin/env python3
"""Build a first practice index from templates paths and explicit problem IDs."""

from __future__ import annotations

import collections
import re
from pathlib import Path
from urllib.parse import quote, urlparse, parse_qs


ROOT = Path(__file__).resolve().parent.parent
TEMPLATES = ROOT / "templates"
ARCHIVE = ROOT / "洛谷" / "code"
CODE_EXTS = {".cpp", ".c", ".py"}
URL_RE = re.compile(rb"https?://[^\s\x00-\x20<>\"']+")
COMMENT_ID_RE = re.compile(rb"(?<![A-Za-z0-9])P(\d{3,6})(?![A-Za-z0-9])", re.I)
SOURCE_REVIEW_EXCEPTIONS = {
    "templates/01_图论/tarjan/tarjan——边双缩点模板.cpp": "P18867 链接未能核实，且文件说明缺少与该题号一致的证据；保留原名。",
    "templates/05_数学数论/数学/高精度——乘法.c": "注释中的 P303 不能可靠确定题号。",
    "templates/05_数学数论/数学/高精度——除法（高对高）.c": "注释写 P1601（加法题），与本文件除法内容冲突。",
}
LEFTIST_ORDER = ["P3377", "P1456", "P1552", "P4971", "P3261", "P3273", "P4331", "P2409", "P2483"]
GENERIC_DEMO_FILES = {
    "templates/01_图论/图论/图——邻接表.cpp",
    "templates/01_图论/图论/图论——A星展示.cpp",
    "templates/02_树上问题/倍增st表/倍增和st表——基础.cpp",
    "templates/02_树上问题/树基础与LCA/二叉树.c",
    "templates/02_树上问题/树基础与LCA/二叉树——前中后遍历.c",
    "templates/03_字符串/前缀树/前缀树——模板.cpp",
    "templates/04_数据结构/左偏树/可持久化左偏树模板-随机对拍.cpp",
    "templates/04_数据结构/平衡树/splay树——展示.cpp",
    "templates/04_数据结构/并查集/并查集——模板.c",
    "templates/04_数据结构/并查集/并查集——模板2.c",
    "templates/04_数据结构/杂项数据结构/位图——模板.cpp",
    "templates/05_数学数论/数学/快速幂——矩阵乘法展示.cpp",
    "templates/05_数学数论/数学/扩展欧几里得——算法展示.cpp",
    "templates/05_数学数论/数学/线性基——异或过程展示.cpp",
    "templates/05_数学数论/数学/逆元——模板.cpp",
    "templates/05_数学数论/数学/高斯消元——加法运算展示.cpp",
    "templates/05_数学数论/数学/高斯消元——同余运算展示.cpp",
    "templates/05_数学数论/数学/高斯消元——异或运算展示.cpp",
    "templates/05_数学数论/数学/高精度——模板.cpp",
    "templates/05_数学数论/数论/莫比乌斯函数——模板.cpp",
    "templates/07_搜索与贪心/单调队列单调栈/单调栈——模板.cpp",
    "templates/09_基础技巧/位运算/二进位制打印.c",
    "templates/09_基础技巧/位运算/位运算的加减乘除.c",
    "templates/09_基础技巧/位运算/位运算的神奇操作.c",
    "templates/09_基础技巧/位运算/异或的神奇操作.c",
    "templates/09_基础技巧/基础技巧/递归函数.c",
    "templates/09_基础技巧/排序/归并分治.c",
    "templates/09_基础技巧/排序/归并排序.c",
    "templates/09_基础技巧/排序/排序——三傻排序.c",
    "templates/09_基础技巧/排序/排序——三大高级排序.c",
    "templates/09_基础技巧/排序/排序——基数排序.c",
    "templates/09_基础技巧/排序/排序——堆排序.c",
    "templates/09_基础技巧/排序/排序——随机快速排序.c",
    "templates/09_基础技巧/排序/排序——随机快速排序2.c",
    "templates/模板/仙人掌树/仙人掌树——找环模板.cpp",
}


def urls(data: bytes) -> list[str]:
    return [m.decode("ascii", "ignore").rstrip(".,;:") for m in URL_RE.findall(data)]


def parse_problem_url(value: str) -> tuple[str, str, int] | None:
    """Return (stable problem ID, source URL, priority); smaller priority wins."""
    value = value.rstrip("/()") + ("/" if value.endswith("/") else "")
    parsed = urlparse(value)
    host = parsed.netloc.lower().removeprefix("www.")
    path = parsed.path
    if host == "luogu.com.cn":
        m = re.fullmatch(r"/problem/solution/(P\d+)", path, re.I)
        if m:
            number = m[1].upper()
            return number, "https://www.luogu.com.cn/problem/" + number, 1
        m = re.fullmatch(r"/problem/([A-Za-z0-9_]+)", path)
        if not m:
            return None
        raw = m[1]
        if re.fullmatch(r"[PB]\d+", raw, re.I):
            return raw.upper(), value, 1
        if re.fullmatch(r"CF\d+[A-Z]\d?", raw, re.I):
            return raw.upper(), value, 2
        if re.fullmatch(r"AT_[A-Za-z0-9_]+", raw, re.I):
            return "AT_" + raw[3:].replace("_", "").upper(), value, 2
        if re.fullmatch(r"SP\d+", raw, re.I):
            return raw.upper(), value, 2
        if re.fullmatch(r"U\d+", raw, re.I):
            return raw.upper(), value, 1
        if re.fullmatch(r"UVA\d+", raw, re.I):
            return raw.upper(), value, 2
        return None
    if host == "codeforces.com":
        m = re.fullmatch(r"/(?:problemset/problem|contest)/(\d+)/(\w+)", path)
        if m:
            return "CF" + m[1] + m[2].upper(), value, 0
        m = re.fullmatch(r"/gym/(\d+)/problem/(\w+)", path)
        if m:
            return "CFGYM" + m[1] + m[2].upper(), value, 0
    if host == "atcoder.jp":
        m = re.fullmatch(r"/contests/([a-z0-9_]+)/tasks/([a-z0-9_]+)", path, re.I)
        if m:
            return "AT_" + m[2].replace("_", "").upper(), value, 0
    if host == "acm.hdu.edu.cn" and path == "/showproblem.php":
        n = parse_qs(parsed.query).get("pid", [""])[0]
        if n.isdigit():
            return "HDU" + n, value, 0
    if host == "poj.org" and path == "/problem":
        n = parse_qs(parsed.query).get("id", [""])[0]
        if n.isdigit():
            return "POJ" + n, value, 0
    if host == "loj.ac":
        m = re.fullmatch(r"/p/(\d+)", path)
        if m:
            return "LOJ" + m[1], value, 0
    if host == "uoj.ac":
        m = re.fullmatch(r"/problem/(\d+)", path)
        if m:
            return "UOJ" + m[1], value, 0
    if host == "spoj.com":
        m = re.fullmatch(r"/(?:SPOJ/)?problems/([A-Za-z0-9_]+)(?:/.*)?", path)
        if m:
            return "SPOJ_" + m[1].upper(), value, 0
    if host == "onlinejudge.org":
        m = re.fullmatch(r"/external/\d+/(\d+)\.html", path)
        if m:
            return "UVA" + m[1], value, 0
        internal = parse_qs(parsed.query).get("problem", [""])[0]
        # These internal IDs were checked against the numbered official pages.
        if internal in {"396": "455", "3384": "12232"}:
            return "UVA" + {"396": "455", "3384": "12232"}[internal], value, 0
    if host == "lightoj.com" and path == "/problem/how-many-points":
        # The official page displays LOJ-1077, distinct from LibreOJ's LOJ.
        return "LIGHTOJ1077", value, 0
    if host == "leetcode.cn":
        m = re.fullmatch(r"/problems/([A-Za-z0-9-]+)/?", path)
        if m:
            return "LC_" + m[1].replace("-", "_").upper(), value, 0
    if host == "ac.nowcoder.com":
        m = re.fullmatch(r"/acm/contest/(\d+)/([A-Za-z0-9]+)", path)
        if m:
            return "NC_" + m[1] + "_" + m[2].upper(), value, 0
    if host == "nowcoder.com":
        m = re.fullmatch(r"/practice/([0-9a-f-]+)", path, re.I)
        if m:
            return "NC_PRACTICE_" + m[1].upper(), value, 0
    if host == "darkbzoj.cc":
        m = re.fullmatch(r"/problem/(\d+)", path)
        if m:
            return "BZOJ" + m[1], value, 0
    if host == "vjudge.net":
        m = re.fullmatch(r"/problem/HDU-(\d+)", path, re.I)
        if m:
            return "HDU" + m[1], "https://acm.hdu.edu.cn/showproblem.php?pid=" + m[1], 1
    if host == "lanqiao.cn":
        m = re.fullmatch(r"/problems/(\d+)/learning/?", path)
        if m:
            return "LQ" + m[1], value, 0
    return None


def comment_problem_id(data: bytes) -> str | None:
    found = set()
    for line in data.splitlines()[:25]:
        if not line.lstrip().startswith((b"//", b"/*", b"*")):
            continue
        found.update(int(x) for x in COMMENT_ID_RE.findall(line))
    if len(found) == 1:
        number = found.pop()
        if number >= 1000:
            return f"P{number}"
    return None


def identify(path: Path) -> tuple[tuple[str, str] | None, str | None]:
    rel = path.relative_to(ROOT).as_posix()
    if rel in SOURCE_REVIEW_EXCEPTIONS:
        return None, SOURCE_REVIEW_EXCEPTIONS[rel]
    data = path.read_bytes()
    found: dict[str, tuple[str, int]] = {}
    for source in urls(data):
        result = parse_problem_url(source)
        if result:
            problem, link, priority = result
            if problem not in found or priority < found[problem][1]:
                found[problem] = (link, priority)
    # A Luogu SP mirror and a SPOJ slug in the same file refer to the same task.
    mirror_sp = [key for key in found if re.fullmatch(r"SP\d+", key)]
    official_sp = [key for key in found if key.startswith("SPOJ_")]
    if len(mirror_sp) == len(official_sp) == 1:
        del found[mirror_sp[0]]
    if len(found) > 1:
        return None, "同一文件出现不同题号：" + "、".join(sorted(found))
    if found:
        problem = next(iter(found))
        # A clear OJ number in the filename must agree with the source link.
        m = re.match(r"^(P\d+|CF\d+[A-Z]\d?|HDU\d+|UOJ\d+|LOJ\d+)", path.stem, re.I)
        if m and m[1].upper() != problem:
            return None, f"文件名 {m[1]} 与原题链接 {problem} 冲突。"
        return (problem, found[problem][0]), None
    comment_id = comment_problem_id(data)
    if comment_id:
        return (comment_id, "https://www.luogu.com.cn/problem/" + comment_id), None
    if urls(data):
        return None, "已有 URL，但无法可靠提取原 OJ 题号。"
    return None, None


def filename_id(name: str) -> str | None:
    stem = Path(name).stem
    m = re.fullmatch(r"((?:P|B|CFGYM|CF|HDU|POJ|LOJ|UOJ|SPOJ_|AT_|LC)\w+?)(?:_\d+)?", stem, re.I)
    return m[1].upper() if m else None


def is_generic_demo(path: Path) -> bool:
    """Only exclude manually reviewed reusable templates and demonstrations."""
    return path.relative_to(ROOT).as_posix() in GENERIC_DEMO_FILES


def link_to_file(path: Path) -> str:
    relative = path.relative_to(ROOT).as_posix()
    return f"[{path.name}](../{quote(relative, safe='/')})"


def problem_sort_key(problem: str) -> tuple[str, int, str]:
    m = re.match(r"([A-Z_]+)(\d+)(.*)", problem)
    if m:
        return m[1], int(m[2]), m[3]
    return problem, 0, ""


def archive_index() -> tuple[dict[str, list[Path]], dict[str, list[Path]]]:
    by_id: dict[str, list[Path]] = collections.defaultdict(list)
    by_url: dict[str, list[Path]] = collections.defaultdict(list)
    review_path = ARCHIVE / "链接待复核清单.md"
    review = set(re.findall(r"^\| ([^|]+\.\w+) \|", review_path.read_text(encoding="utf-8"), re.M)) if review_path.exists() else set()
    for path in ARCHIVE.iterdir():
        if path.suffix.lower() not in CODE_EXTS or path.name in review:
            continue
        data = path.read_bytes()
        if not data.strip():
            continue
        key = filename_id(path.name)
        if key:
            by_id[key].append(path)
        for source in urls(data):
            parsed = parse_problem_url(source)
            if parsed and key and (key == parsed[0] or (key.startswith("SPOJ_") and parsed[0].startswith("SP")) or key.startswith("LC")):
                by_url[parsed[0]].append(path)
    return by_id, by_url


def main() -> None:
    code = sorted(path for path in TEMPLATES.rglob("*") if path.suffix.lower() in CODE_EXTS)
    groups: dict[tuple[str, str], dict[str, dict]] = collections.defaultdict(dict)
    unresolved: list[tuple[Path, str]] = []
    candidates: list[tuple[Path, str, str]] = []
    source_files = 0
    generic_demos = 0
    utilities = 0
    for path in code:
        if path.name == "count.py" and path.parent.name == "tools":
            utilities += 1
            continue
        identified, issue = identify(path)
        if issue:
            unresolved.append((path, issue))
        if not identified:
            if not issue:
                if is_generic_demo(path):
                    generic_demos += 1
                else:
                    unresolved.append((path, "没有可核实的 OJ 编号；需判断是否为具体练习题。"))
            continue
        problem, source = identified
        source_files += 1
        rel_parts = path.relative_to(TEMPLATES).parts
        top = rel_parts[0]
        topic = " / ".join(rel_parts[1:-1]) or "综合"
        if topic == top.removeprefix(top[:3]) and re.match(r"\d\d_", top):
            topic += "（综合）"
        item = groups[(top, topic)].setdefault(problem, {"source": source, "files": []})
        item["files"].append(path)
        if not re.fullmatch(re.escape(problem) + r"(?:_[2-9]\d*)?", path.stem, re.I):
            if problem.startswith("LC_"):
                reason = "原题 slug 已确认，但数字题号未核实；不以英文题名改名。"
            elif problem.startswith("NC_PRACTICE_"):
                reason = "牛客 practice UUID 已确认，但不符合现有比赛编号规则。"
            else:
                reason = "题号已确认，文件名待规范。"
            candidates.append((path, problem, reason))

    by_id, by_url = archive_index()
    all_problem_ids = {problem for entries in groups.values() for problem in entries}
    covered: set[str] = set()
    only_templates: set[str] = set()
    associations = collections.Counter()
    topic_sizes = {}
    lines = [
        "# 算法学习题单",
        "",
        f"当前收录 **{len(all_problem_ids)}** 道题，覆盖 **{len(groups)}** 个现有目录知识点。",
        "",
        "第一版仅依据 `templates` 现有目录与文件中的明确题号、原题链接建立对应关系。目录表示本仓库的学习归类；同一题可以属于多个目录。题目按编号排列，不代表难度。",
        "",
        "## 使用方式",
        "",
        "1. 从下方目录选择知识点，先看对应的 `templates` 代码，再打开原题。",
        "2. `洛谷/code` 栏列出已有的同题练习版本；“仅 templates 中存在”表示本轮未找到对应刷题文件，不代表未做过。",
        "3. 真正的模板文件、来源冲突项暂不列为练习题；待确认项见[命名候选清单](templates%E7%BB%83%E4%B9%A0%E9%A2%98%E5%91%BD%E5%90%8D%E5%80%99%E9%80%89%E6%B8%85%E5%8D%95.md)。",
        "纯模板目录若没有可确认的独立练习题，本版不建立空表。",
        "",
        "## 分类导航",
        "",
    ]
    top_names = {"模板": "历史模板区"}
    for top in sorted({key[0] for key in groups}):
        title = top_names.get(top, re.sub(r"^\d\d_", "", top))
        lines.append(f"- [{title}](#{title})")
    lines.append("")
    for top in sorted({key[0] for key in groups}):
        title = top_names.get(top, re.sub(r"^\d\d_", "", top))
        lines.extend([f"## {title}", ""])
        for _, topic in sorted((key for key in groups if key[0] == top), key=lambda x: x[1]):
            entries = groups[(top, topic)]
            topic_sizes[f"{title} / {topic}"] = len(entries)
            lines.extend([f"### {topic}", ""])
            if top == "04_数据结构" and topic == "左偏树":
                lines.extend(["建议先读基础模板与 P3377、P1456，再看 P1552、P4971、P3261、P3273、P4331，最后读可持久化模板、P2409 与 P2483；详见本目录 README。", ""])
            lines.extend(["| 题号 | 原题 | templates 代码 | 洛谷/code |", "| --- | --- | --- | --- |"])
            ordered = sorted(entries, key=problem_sort_key)
            if top == "04_数据结构" and topic == "左偏树":
                ordered = sorted(entries, key=lambda x: (LEFTIST_ORDER.index(x) if x in LEFTIST_ORDER else 999, problem_sort_key(x)))
            for problem in ordered:
                item = entries[problem]
                source_files_here = sorted(item["files"], key=lambda p: p.name)
                archive_files = sorted(set(by_id.get(problem, []) + by_url.get(problem, [])), key=lambda p: (not bool(re.fullmatch(re.escape(problem) + r"\.[^.]+", p.name, re.I)), p.name))
                if archive_files:
                    covered.add(problem)
                else:
                    only_templates.add(problem)
                associations[problem] += 1
                template_cell = "、".join(link_to_file(p) for p in source_files_here)
                archive_cell = "、".join(link_to_file(p) for p in archive_files) if archive_files else "仅 templates 中存在"
                lines.append(f"| {problem} | [原题]({item['source']}) | {template_cell} | {archive_cell} |")
            lines.append("")
    (ROOT / "docs" / "算法学习题单.md").write_text("\n".join(lines), encoding="utf-8")

    candidate_lines = ["# templates 练习题命名候选清单", "", f"当前有 **{len(candidates)}** 份已确认来源但正式编号或文件名待处理的文件、**{len(unresolved)}** 份来源或用途待确认文件。", ""]
    if candidates:
        candidate_lines.extend(["## 已知来源，编号或命名待处理", "", "| 当前文件 | 来源线索 | 原因 |", "| --- | --- | --- |"])
        for path, problem, reason in sorted(candidates, key=lambda pair: pair[0].as_posix()):
            candidate_lines.append(f"| {link_to_file(path)} | {problem} | {reason} |")
        candidate_lines.append("")
    candidate_lines.extend(["## 来源或用途待确认", "", "下列文件的现有题号、链接或用途信息不足以安全改名；已确认的通用模板与算法演示不在此列。", "", "| 文件 | 原因 |", "| --- | --- |"])
    for path, reason in sorted(unresolved, key=lambda pair: pair[0].as_posix()):
        candidate_lines.append(f"| {link_to_file(path)} | {reason} |")
    candidate_lines.append("")
    (ROOT / "docs" / "templates练习题命名候选清单.md").write_text("\n".join(candidate_lines), encoding="utf-8")

    print("templates_code", len(code))
    print("identified_source_files", source_files)
    print("unique_problems", len(associations))
    print("knowledge_points", len(groups))
    print("archive_covered", len(covered))
    print("only_templates", len(only_templates - covered))
    print("multi_topic_problems", sum(n > 1 for n in associations.values()))
    print("unresolved_source_files", len(unresolved))
    print("confirmed_generic_demos", generic_demos)
    print("utilities", utilities)
    print("noncanonical_practice_files", len(candidates))
    print("top_topics", sorted(topic_sizes.items(), key=lambda x: (-x[1], x[0]))[:10])


if __name__ == "__main__":
    main()
