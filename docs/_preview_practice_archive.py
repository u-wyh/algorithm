#!/usr/bin/env python3
"""Preview platform folders and build an index from source header tags."""

from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
from urllib.parse import quote

from _build_algorithm_practice_list import ARCHIVE, CODE_EXTS, parse_problem_url, problem_sort_key


URL = re.compile(r'https?://[^\s<>"、，。；）】]+')
TAG = re.compile(r"^算法标签\s*[:：]\s*(.+)$")
IMPLEMENTATION_STATUS = re.compile(r"^实现状态\s*[:：]\s*(.+)$")
LUOGU = re.compile(r"([PBUT])(\d+)")
CURRENT_PROBLEM = re.compile(r"^(?:实际对应|原题现址)\s*[:：]")
PLATFORMS = {
    "CF": "Codeforces",
    "CFGYM": "Codeforces",
    "AT_": "AtCoder",
    "HDU": "HDU",
    "LC_": "LeetCode",
    "LOJ": "LibreOJ",
    "UOJ": "UOJ",
    "QOJ": "QOJ",
    "SP": "SPOJ",
    "SPOJ_": "SPOJ",
    "UVA": "UVa",
    "POJ": "POJ",
    "NC_": "牛客",
    "LQ": "蓝桥杯",
    "BZOJ": "DarkBZOJ",
    "LIGHTOJ": "LightOJ",
}

TOPIC_RULES = {
    "动态规划": (
        r"动态规划|背包|数位.?dp|\bdp\b|记忆化|状态压缩|递推|滚动数组|"
        r"最长上升子序列|最长不下降子序列|最长公共子序列|最大子段和"
    ),
    "图论": (
        r"最短路|dijkstra|spfa|floyd|bellman|tarjan|kruskal|prim|最小生成树|拓扑|图论|"
        r"二分图|圆方树|虚树|树上|树链|最近公共祖先|lca|连通分量|割点|桥|建图|网络流|"
        r"最大流|费用流|最小割|dinic|欧拉回路|基环树|树的直径|分层图|2-sat|传递闭包|缩点"
    ),
    "字符串": r"字典树|trie|字符串|kmp|manacher|回文|ac自动机|后缀|前缀函数|字符串哈希",
    "数学与数论": (
        r"数学|数论|整除|素数|质数|筛法|线性筛|欧拉筛|组合|计数|容斥|概率|期望|矩阵|"
        r"逆元|莫比乌斯|欧拉函数|lucas|快速幂|多项式|fft|ntt|博弈|线性基|高精度|"
        r"欧几里得|最大公约数|同余|剩余定理|生成函数|卡特兰|高斯消元|bsgs|"
        r"斐波那契|卢卡斯|试除法|sg函数|分数规划"
    ),
    "计算几何": r"几何|凸包|向量|极角|叉积|面积|扫描线|旋转卡壳|半平面交",
    "数据结构": (
        r"线段树|树状数组|并查集|平衡树|堆|栈|队列|稀疏表|st表|treap|splay|avl|哈希|"
        r"分块|启发式合并|数据结构|莫队|笛卡尔树|左偏树|替罪羊树|k[- ]?d.?tree|kd树|"
        r"lct|动态树|链表|有序集合|懒标记|二叉树|点分树|\bmap\b|\bmultiset\b|\bset\b"
    ),
    "搜索与贪心": r"搜索|贪心|枚举|回溯|剪枝|bfs|dfs",
    "基础技巧": (
        r"模拟|排序|二分|三分|前缀和|差分|双指针|滑动窗口|位运算|构造|离散化|扫描|"
        r"倍增|分治|逆序对|分类讨论|离线|bitset|二进制分组|打表|区间合并|随机化|递归|中位数"
    ),
}


@dataclass
class Entry:
    source: str
    sha256: str
    destination: str | None = None
    platform: str | None = None
    problem: str | None = None
    link: str | None = None
    tags: tuple[str, ...] = ()
    implementation_status: str | None = None
    review: str | None = None


def header_lines(data: bytes, is_python: bool) -> list[str]:
    try:
        text = data.decode("utf-8-sig")
    except UnicodeDecodeError:
        text = data.decode("gb18030", errors="replace")

    lines = []
    in_block = False
    for line in text.splitlines():
        line = line.lstrip()
        if is_python and line.startswith("#"):
            lines.append(line[1:].strip())
        elif not is_python and (in_block or line.startswith("/*")):
            comment = line if in_block else line[2:]
            comment, closer, tail = comment.partition("*/")
            lines.append(comment.strip().lstrip("*").strip())
            in_block = not closer
            if tail.strip() and not tail.lstrip().startswith("//"):
                break
        elif not is_python and line.startswith("//"):
            lines.append(line[2:].strip())
        elif line:
            break
    return lines


def header_problem(lines: list[str]) -> tuple[str | None, str | None, str | None]:
    found: dict[str, tuple[int, str]] = {}
    explicit = set()
    all_links = False
    for line in lines:
        for link in URL.findall(line):
            link = link.rstrip(".,;:)]")
            all_links = True
            result = parse_problem_url(link)
            if not result:
                continue
            problem, link, priority = result
            if problem not in found or priority < found[problem][0]:
                found[problem] = (priority, link)
            if CURRENT_PROBLEM.match(line):
                explicit.add(problem)

    candidates = explicit or set(found)
    if candidates == {"SP8791", "SPOJ_DYNALCA"}:
        candidates = {"SPOJ_DYNALCA"}
    if candidates == {"SP2878", "SPOJ_KNIGHTS"}:
        return "SPOJ_KNIGHTS", found["SP2878"][1], None
    if candidates == {"P3513", "LOJ2155"}:
        candidates = {"P3513"}
    if len(candidates) == 1:
        problem = next(iter(candidates))
        return problem, found[problem][1], None
    if candidates:
        return None, None, "有多个题号：" + "、".join(sorted(candidates))
    return None, None, "题目链接需复核" if all_links else "未找到题目链接"


def destination(problem: str, name: str) -> tuple[str, str]:
    match = LUOGU.fullmatch(problem)
    if match:
        prefix, number = match.groups()
        number = int(number)
        large_start = number // 500 * 500
        small_start = number // 100 * 100
        large = f"{prefix}{large_start:04d}-{prefix}{large_start + 499:04d}"
        small = f"{prefix}{small_start:04d}-{prefix}{small_start + 99:04d}"
        return "洛谷", f"洛谷/{large}/{small}/{name}"

    prefix = re.match(r"^[A-Z]+_?", problem)[0]
    platform = PLATFORMS[prefix]
    return platform, f"{platform}/{name}"


def scan_archive(archive: Path) -> list[Entry]:
    plan = []
    by_destination = defaultdict(list)
    for path in sorted(archive.rglob("*")):
        if not path.is_file() or path.is_symlink() or path.suffix.lower() not in CODE_EXTS:
            continue
        data = path.read_bytes()
        lines = header_lines(data, path.suffix.lower() == ".py")
        tags = [match[1] for line in lines if (match := TAG.fullmatch(line))]
        status = next((match[1] for line in lines if (match := IMPLEMENTATION_STATUS.fullmatch(line))), None)
        problem, link, review = header_problem(lines)
        entry = Entry(
            source=path.relative_to(archive).as_posix(),
            sha256=hashlib.sha256(data).hexdigest(),
            problem=problem,
            link=link,
            tags=tuple(dict.fromkeys(tag.strip() for tag in tags[0].split("、") if tag.strip())) if len(tags) == 1 else (),
            implementation_status=status,
            review=review,
        )
        if problem:
            entry.platform, entry.destination = destination(problem, path.name)
            by_destination[entry.destination.casefold()].append(entry)
        plan.append(entry)

    for entries in by_destination.values():
        if len(entries) > 1:
            for entry in entries:
                entry.review = "归档路径与其他源码重名"
                entry.destination = None
    return plan


def render_tag_groups(path: Path, archive: Path, groups: dict) -> list[str]:
    lines = []
    for tag, entries in sorted(groups.items(), key=lambda item: (-len(item[1]), item[0])):
        lines.extend((f"## {tag}（{len(entries)} 题）", ""))
        for (platform, problem), versions in sorted(
            entries.items(), key=lambda item: (item[0][0], problem_sort_key(item[0][1]))
        ):
            sources = []
            for entry in versions:
                local = Path(os.path.relpath(archive / entry.source, path.parent)).as_posix()
                name = PurePosixPath(entry.source).name.replace("[", "\\[").replace("]", "\\]")
                sources.append(f"[{name}]({quote(local, safe='/')})")
            lines.append(f"- {platform} [{problem}](<{versions[0].link}>) · " + "、".join(sources))
        lines.append("")
    return lines


def write_index(
    path: Path, archive: Path, plan: list[Entry], *, archived_only: bool = False
) -> tuple[int, int]:
    by_tag = defaultdict(lambda: defaultdict(list))
    problems = set()
    for entry in plan:
        if entry.review or entry.implementation_status or (archived_only and entry.source != entry.destination):
            continue
        for tag in entry.tags:
            key = (entry.platform, entry.problem)
            by_tag[tag][key].append(entry)
            problems.add(key)

    lines = [
        "# 按算法标签练习",
        "",
        f"共 {len(by_tag)} 个标签，覆盖 {len(problems)} 道题。",
        "同题的多份实现合并展示。每个标签下仅列出使用该算法的版本。",
        "",
    ]
    if archived_only:
        sections = {topic: {} for topic in (*TOPIC_RULES, "其他技巧")}
        for tag, entries in by_tag.items():
            topic = next(
                (topic for topic, rule in TOPIC_RULES.items() if re.search(rule, tag, re.I)),
                "其他技巧",
            )
            sections[topic][tag] = entries
        directory = path.with_suffix("")
        directory.mkdir(exist_ok=True)
        lines.extend(("| 专题 | 标签数 | 不同题目数 |", "| --- | ---: | ---: |"))
        for topic, groups in sections.items():
            if not groups:
                continue
            page = directory / f"{topic}.md"
            relative_page = quote(page.relative_to(path.parent).as_posix(), safe="/")
            topic_problems = {key for entries in groups.values() for key in entries}
            lines.append(f"| [{topic}]({relative_page}) | {len(groups)} | {len(topic_problems)} |")
            page_lines = [f"# {topic}", "", f"[返回算法题单](../{quote(path.name)})", ""]
            page_lines.extend(render_tag_groups(page, archive, groups))
            page.write_text("\n".join(page_lines), encoding="utf-8")
        lines.extend(("", "一道题可以出现在多个专题里，各专题的题目数可以重叠。", ""))
    else:
        lines.extend(render_tag_groups(path, archive, by_tag))
    path.write_text("\n".join(lines), encoding="utf-8")
    return len(by_tag), len(problems)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--archive", type=Path, default=ARCHIVE)
    output_type = parser.add_mutually_exclusive_group(required=True)
    output_type.add_argument("--output", type=Path, help="保存归档预演及题单的目录")
    output_type.add_argument("--index", type=Path, help="生成已归档题目的 Markdown 题单")
    args = parser.parse_args()
    archive = args.archive.resolve()
    output = (args.index or args.output).resolve()
    if not archive.is_dir():
        parser.error(f"找不到源码目录：{archive}")
    if output.is_relative_to(archive):
        parser.error("输出必须在源码目录外。")

    plan = scan_archive(archive)
    if args.index:
        if output.suffix.lower() != ".md":
            parser.error("题单的扩展名必须为 .md。")
        output.parent.mkdir(parents=True, exist_ok=True)
        labels, problems = write_index(output, archive, plan, archived_only=True)
        print(f"练习题单：{labels} 个算法标签，{problems} 道不同题目。")
        return

    output.mkdir(parents=True, exist_ok=True)
    (output / "归档预演.json").write_text(
        json.dumps([asdict(entry) for entry in plan], ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    labels, problems = write_index(output / "按算法标签练习（预览）.md", archive, plan)
    platforms = Counter(entry.platform for entry in plan if entry.destination)
    print(f"源码 {len(plan)} 份，可归档 {sum(platforms.values())} 份，待复核 {sum(bool(entry.review) for entry in plan)} 份。")
    print("平台统计：" + "、".join(f"{name} {count}" for name, count in platforms.most_common()))
    print(f"练习题单：{labels} 个算法标签，{problems} 道不同题目。")


if __name__ == "__main__":
    main()
