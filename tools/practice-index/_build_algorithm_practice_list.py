#!/usr/bin/env python3
"""Build a first practice index from templates paths and explicit problem IDs."""

from __future__ import annotations

import collections
import re
from pathlib import Path
from urllib.parse import quote, urlparse, parse_qs


TOOL_DIR = Path(__file__).resolve().parent
ROOT = TOOL_DIR.parents[1]
TEMPLATES = ROOT / "templates"
ARCHIVE = ROOT / "practices" / "code"
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
    value = value.rstrip(".,;:、，。；）)]")
    try:
        parsed = urlparse(value)
        host = (parsed.hostname or "").lower().removeprefix("www.")
    except ValueError:
        return None
    path = parsed.path.rstrip("/")
    if host == "luogu.com.cn":
        m = re.fullmatch(r"/problem/solution/(P\d+)", path, re.I)
        if m:
            number = m[1].upper()
            return number, "https://www.luogu.com.cn/problem/" + number, 1
        m = re.fullmatch(r"/problem/([A-Za-z0-9_]+)", path)
        if not m:
            return None
        raw = m[1]
        if re.fullmatch(r"[PBT]\d+", raw, re.I):
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
        m = re.fullmatch(r"/(?:problemset/problem/(\d+)|contest/(\d+)(?:/problem)?)/(\w+)", path)
        if m:
            return "CF" + (m[1] or m[2]) + m[3].upper(), value, 0
        m = re.fullmatch(r"/gym/(\d+)/problem/(\w+)", path)
        if m:
            return "CFGYM" + m[1] + m[2].upper(), value, 0
    if host == "atcoder.jp":
        m = re.fullmatch(r"/contests/[a-z0-9_-]+/tasks/([a-z0-9_-]+)", path, re.I)
        if m:
            return "AT_" + m[1].replace("_", "").replace("-", "").upper(), value, 0
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
    if host == "spoj.com" or host.endswith(".spoj.com"):
        m = re.fullmatch(r"/(?:SPOJ/)?problems/([A-Za-z0-9_]+)(?:/.*)?", path)
        if m:
            return "SPOJ_" + m[1].upper(), value, 0
    if host == "onlinejudge.org":
        m = re.fullmatch(r"/external/\d+/(\d+)\.(?:html|pdf)", path, re.I)
        if m:
            return "UVA" + m[1], value, 0
        internal = parse_qs(parsed.query).get("problem", [""])[0]
        # These internal IDs were checked against the numbered official pages.
        if internal in {"396": "455", "3384": "12232"}:
            return "UVA" + {"396": "455", "3384": "12232"}[internal], value, 0
    if host == "lightoj.com" and path == "/problem/how-many-points":
        # The official page displays LOJ-1077, distinct from LibreOJ's LOJ.
        return "LIGHTOJ1077", value, 0
    if host in {"leetcode.cn", "leetcode.com"}:
        m = re.fullmatch(r"/problems/([A-Za-z0-9-]+)(?:/description)?", path)
        if m:
            return "LC_" + m[1].replace("-", "_").upper(), value, 0
    if host == "qoj.ac":
        m = re.fullmatch(r"/(?:contest/\d+/)?problem/(\d+)(?:/statement(?:/[a-z-]+)?)?", path, re.I)
        if m:
            return "QOJ" + m[1], value, 0
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
    m = re.fullmatch(r"((?:P|B|CFGYM|CF|HDU|POJ|LOJ|UOJ|QOJ|UVA|SPOJ_|SP|AT_|LC)\w+?)(?:_\d+)?", stem, re.I)
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
    for path in ARCHIVE.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in CODE_EXTS:
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
    unresolved = 0
    source_files = 0
    generic_demos = 0
    utilities = 0
    for path in code:
        if path.name == "count.py" and path.parent.name == "tools":
            utilities += 1
            continue
        identified, issue = identify(path)
        if not identified:
            if not issue and is_generic_demo(path):
                generic_demos += 1
            else:
                unresolved += 1
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
        "查找 `practices/code` 中的练习，可打开[全量算法练习清单](全量算法练习清单.md)。本页按 `templates` 中的知识点组织。",
        "",
        "本题单主要依据 [`templates` 算法知识地图](../templates/README.md)中的现有分类，以及文件中的明确题号和原题链接整理。目录表示这份代码在本仓库中的学习归属；一道题可能有多种做法，也可以出现在多个知识点下。题目按编号排列，不代表难度。",
        "",
        "## 使用方式",
        "",
        "1. 从下方目录选择知识点，先看对应的 `templates` 代码，再打开原题。",
        "2. `practices/code` 栏列出归档中的同题实现。打开源码可查看文件头的[难度评分](../practices/code/README.md#难度评分)。只在 `templates` 中找到实现的题目会注明。",
        "",
        "## 分类导航",
        "",
    ]
    top_names = {"模板": "历史模板区"}
    tops = sorted({key[0] for key in groups})
    for top_index, top in enumerate(tops, 1):
        title = top_names.get(top, re.sub(r"^\d\d_", "", top))
        lines.append(f"- [{title}](#section-{top_index:02d})")
        topics = sorted((key[1] for key in groups if key[0] == top))
        for topic_index, topic in enumerate(topics, 1):
            lines.append(f"  - [{topic}（{len(groups[(top, topic)])} 题）](#study-{top_index:02d}-{topic_index:02d})")
    lines.append("")
    for top_index, top in enumerate(tops, 1):
        title = top_names.get(top, re.sub(r"^\d\d_", "", top))
        lines.extend([f'<a id="section-{top_index:02d}"></a>', f"## {title}", ""])
        topics = sorted((key[1] for key in groups if key[0] == top))
        for topic_index, topic in enumerate(topics, 1):
            entries = groups[(top, topic)]
            topic_sizes[f"{title} / {topic}"] = len(entries)
            lines.extend([f'<a id="study-{top_index:02d}-{topic_index:02d}"></a>', f"### {topic}", ""])
            if top == "04_数据结构" and topic == "左偏树":
                lines.extend(["建议先读基础模板与 P3377、P1456，再看 P1552、P4971、P3261、P3273、P4331，最后读可持久化模板、P2409 与 P2483；详见本目录 README。", ""])
            lines.extend(["| 题号 | 原题 | 模板代码 | 练习实现 |", "| --- | --- | --- | --- |"])
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

    print("templates_code", len(code))
    print("identified_source_files", source_files)
    print("unique_problems", len(associations))
    print("knowledge_points", len(groups))
    print("archive_covered", len(covered))
    print("only_templates", len(only_templates - covered))
    print("multi_topic_problems", sum(n > 1 for n in associations.values()))
    print("unresolved_source_files", unresolved)
    print("confirmed_generic_demos", generic_demos)
    print("utilities", utilities)
    print("top_topics", sorted(topic_sizes.items(), key=lambda x: (-x[1], x[0]))[:10])


if __name__ == "__main__":
    main()
