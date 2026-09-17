#!/usr/bin/env python3
"""Build the complete practice-code index from local evidence and saved OJ tags."""

from __future__ import annotations

import collections
import importlib.util
import json
import re
from pathlib import Path
from urllib.parse import quote


ROOT = Path(__file__).resolve().parent.parent
ARCHIVE = ROOT / "洛谷" / "code"
TEMPLATES = ROOT / "templates"
SNAPSHOT = ROOT / "docs" / "练习题官方标签快照.json"
OUTPUT = ROOT / "docs" / "全量算法练习清单.md"
TRAINING = ROOT / "洛谷" / "练习赛"
TRAINING_OUTPUT = ROOT / "docs" / "练习赛代码索引.md"
EXTENSIONS = {".cpp", ".c", ".py"}
CATEGORIES = [
    "图论", "树上问题", "字符串", "数据结构", "数学数论", "动态规划",
    "搜索与贪心", "离线分治", "基础技巧", "其他程序", "待人工核实",
]
TOP = {f"{i:02}_" + name: name for i, name in enumerate(CATEGORIES[:9], 1)}
ID_RE = re.compile(
    r"(?:P\d+|B\d+|CFGYM\d+[A-Z]\d*|CF\d+[A-Z]\d*|HDU\d+|POJ\d+|"
    r"LOJ\d+|UOJ\d+|UVA\d+|SP\d+|SPOJ_[A-Z0-9_]+|AT_[A-Z0-9_]+|"
    r"LC\d+|U\d+|NC_\d+_[A-Z0-9]+)", re.I
)
CF_CATEGORY = {
    "data structures": "数据结构", "trees": "树上问题", "dp": "动态规划",
    "dfs and similar": "搜索与贪心", "graphs": "图论", "binary search": "基础技巧",
    "divide and conquer": "基础技巧", "math": "数学数论", "dsu": "数据结构",
    "greedy": "搜索与贪心", "implementation": "基础技巧",
    "brute force": "搜索与贪心", "bitmasks": "基础技巧",
    "hashing": "字符串", "combinatorics": "数学数论", "sortings": "基础技巧",
    "shortest paths": "图论", "strings": "字符串", "probabilities": "数学数论",
    "constructive algorithms": "基础技巧", "number theory": "数学数论",
    "string suffix structures": "字符串", "2-sat": "图论", "games": "数学数论",
    "meet-in-the-middle": "搜索与贪心", "interactive": "基础技巧",
    "fft": "数学数论", "flows": "图论", "two pointers": "基础技巧",
    "geometry": "数学数论", "ternary search": "基础技巧", "matrices": "数学数论",
}
NAME_HINTS = [
    ("tarjan", "图论"), ("拓扑", "图论"), ("kmp", "字符串"),
    ("前缀树", "字符串"), ("哈希", "字符串"), ("线段树", "数据结构"),
    ("左偏树", "数据结构"), ("AVL", "数据结构"), ("数位dp", "动态规划"),
]
LEGACY_TOPICS = {
    "2sat": "图论", "基环树": "树上问题", "仙人掌树": "图论",
    "优化建图": "图论", "LCT": "树上问题",
}
# These exceptions have been checked against the local implementation, not inferred
# from a problem title. Leave the rest in the review section when evidence is thin.
CODE_CLASSIFICATION = {
    "AT_AGC010F": ("树上博弈、树形 DP", "树上问题"),
    "AT_ARC069D": ("2-SAT、线段树优化建图", "图论"),
    "B1649": ("网格 DFS", "搜索与贪心"),
    "B3367": ("单调队列", "数据结构"),
    "CFGYM103107A": ("线段树", "数据结构"),
    "FILE:1245D.cpp": ("最小生成树", "图论"),
    "FILE:480764.cpp": ("排序", "基础技巧"),
    "FILE:ATabc308.cpp": ("01 Trie", "数据结构"),
    "FILE:CCPCd.cpp": ("字符串哈希", "字符串"),
    "FILE:T3.cpp": ("二分答案", "基础技巧"),
    "FILE:at145c.cpp": ("组合计数", "数学数论"),
    "FILE:at2014c.cpp": ("莫队", "离线分治"),
    "FILE:at205E.cpp": ("组合计数", "数学数论"),
    "FILE:atarc065.cpp": ("图搜索、集合", "图论"),
    "FILE:t5.cpp": ("DFS 判树", "图论"),
    "FILE:t6.cpp": ("拓扑排序、DAG 动态规划", "图论"),
    "FILE:t9.cpp": ("Treap", "数据结构"),
    "FILE:test6(1).cpp": ("控制台游戏", "其他程序"),
    "FILE:test6(2).cpp": ("控制台游戏", "其他程序"),
    "FILE:第六章1.cpp": ("树的遍历", "树上问题"),
    "HDU1506": ("单调栈", "数据结构"),
    "HDU1521": ("生成函数", "数学数论"),
    "HDU2063": ("二分图匹配", "图论"),
    "HDU3549": ("最大流", "图论"),
    "LC851": ("拓扑排序", "图论"),
    "LC2050": ("拓扑排序、DAG 动态规划", "图论"),
    "LOJ101": ("最大流", "图论"),
    "LOJ116": ("有下界的网络流", "图论"),
    "LOJ117": ("有下界的网络流", "图论"),
    "P225": ("排序、贪心", "搜索与贪心"),
    "P1500": ("最小费用最大流", "图论"),
    "P1732": ("优先队列、贪心", "搜索与贪心"),
    "P1778": ("状态压缩 BFS", "搜索与贪心"),
    "P3156": ("数组查询", "基础技巧"),
    "P3444": ("状态动态规划", "动态规划"),
    "P3447": ("数位 DP", "动态规划"),
    "P3635": ("线性 DP", "动态规划"),
    "P3636": ("线性 DP", "动态规划"),
    "P3679": ("SOS DP、二分图匹配", "动态规划"),
    "P4475": ("KD Tree", "数据结构"),
    "P5098": ("曼哈顿距离变换", "基础技巧"),
    "P5186": ("单调队列", "数据结构"),
    "P6664": ("Link Cut Tree", "树上问题"),
    "P7245": ("最小费用最大流", "图论"),
    "P7947": ("线段树", "数据结构"),
    "P8048": ("莫队", "离线分治"),
    "P8311": ("贪心", "搜索与贪心"),
    "P8312": ("Bellman-Ford", "图论"),
    "P8475": ("树状数组、DFS 序", "树上问题"),
    "P9106": ("构造", "基础技巧"),
    "P9173": ("线性 DP", "动态规划"),
    "P10349": ("前缀和", "基础技巧"),
    "P10575": ("固定输出", "基础技巧"),
    "P12300": ("区间 DP", "动态规划"),
    "CF1746E": ("随机哈希、树状数组", "数据结构"),
    "P13556": ("并查集、生成树", "图论"),
    "SP18185": ("分块", "数据结构"),
    "SP20644": ("莫队", "离线分治"),
    "SPOJ_DYNALCA": ("Link Cut Tree", "树上问题"),
    "SPOJ_GSS3": ("线段树", "数据结构"),
    "UVA1391": ("2-SAT", "图论"),
    "UVA1464": ("圆方树、LCA", "图论"),
    "UVA11526": ("整除分块", "数学数论"),
}
CF_TAG_PRIORITY = [
    "2-sat", "flows", "shortest paths", "dsu", "fft", "string suffix structures",
    "hashing", "trees", "strings", "dp", "graphs", "data structures",
    "divide and conquer", "number theory", "combinatorics", "geometry",
    "greedy", "binary search", "two pointers", "bitmasks", "dfs and similar",
    "sortings", "math", "implementation", "brute force",
]


def load_old_index():
    script = ROOT / "docs" / "_build_algorithm_practice_list.py"
    spec = importlib.util.spec_from_file_location("curated_index", script)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader
    spec.loader.exec_module(module)
    return module


def file_id(path: Path) -> str | None:
    stem = re.sub(r"_\d+$", "", path.stem)
    match = ID_RE.fullmatch(stem)
    return match.group(0).upper() if match else None


def file_link(path: Path) -> str:
    return f"[{path.name}](../{quote(path.relative_to(ROOT).as_posix(), safe='/')})"


def sort_key(problem: str) -> tuple[str, int, str]:
    match = re.match(r"([A-Z_]+)(\d+)(.*)", problem)
    return (match[1], int(match[2]), match[3]) if match else (problem, 0, "")


def luogu_tag_info(ids: list[int], definitions: dict) -> list[tuple[str, str, int]]:
    """Return only the most specific tags, with category and taxonomy depth."""
    present = {str(x) for x in ids if str(x) in definitions}
    ancestors: dict[str, list[str]] = {}
    for tag in present:
        chain = [tag]
        while True:
            parent = definitions[chain[-1]].get("parent")
            if parent is None or str(parent) not in definitions or str(parent) in chain:
                break
            chain.append(str(parent))
        ancestors[tag] = chain
    non_leaves = {parent for chain in ancestors.values() for parent in chain[1:]}
    result = []
    for tag in present - non_leaves:
        chain = ancestors[tag]
        root = int(chain[-1])
        ints = {int(x) for x in chain}
        if root in (11, 44):
            category = "数据结构"
        elif root in (3, 146):
            category = "动态规划"
        elif root == 2:
            category = "字符串"
        elif root == 6:
            category = "图论"
        elif root == 230:
            category = "树上问题"
        elif root == 4:
            category = "搜索与贪心"
        elif root in (5, 8, 13, 69, 72, 246, 252, 266, 271, 278):
            category = "数学数论"
        elif root == 110:
            category = "搜索与贪心" if 7 in ints else "基础技巧"
        elif root == 308:
            if ints & {41, 371, 446, 447}:
                category = "离线分治"
            elif 524 in ints:
                category = "搜索与贪心"
            elif ints & {9, 214, 368}:
                category = "数据结构"
            elif 10 in ints:
                category = "数学数论"
            else:
                category = "基础技巧"
        elif root == 467:
            category = "图论" if 471 in ints else "数学数论"
        else:
            category = "基础技巧"
        result.append((definitions[tag]["name"], category, len(chain)))
    return sorted(result, key=lambda item: (-item[2], CATEGORIES.index(item[1]), item[0]))


def source_link(problem: str, confirmed: str | None, snapshot: dict) -> str | None:
    if problem in {"P225", "CF1746E"}:
        return None  # The stored link does not resolve in the official problem list.
    if confirmed:
        return confirmed
    if problem in snapshot["luogu"] and problem.startswith(("P", "B", "SP")):
        return "https://www.luogu.com.cn/problem/" + problem
    if problem in snapshot["codeforces"]:
        match = re.fullmatch(r"CF(\d+)([A-Z]\d*)", problem)
        if match:
            return f"https://codeforces.com/problemset/problem/{match[1]}/{match[2]}"
    return None


def main() -> None:
    old_index = load_old_index()
    snapshot = json.loads(SNAPSHOT.read_text(encoding="utf-8"))
    definitions = snapshot["tag_defs"]
    records = collections.defaultdict(lambda: {"archive": [], "templates": [], "topics": [], "urls": [], "notes": []})
    archive_paths = sorted(p for p in ARCHIVE.iterdir() if p.suffix.lower() in EXTENSIONS)

    for path in archive_paths:
        name_id = file_id(path)
        identified, issue = old_index.identify(path)
        linked_id = identified[0] if identified else None
        if name_id and linked_id and name_id != linked_id and not (
            name_id.startswith("SPOJ_") and linked_id.startswith("SP")
        ) and not (name_id.startswith("LC") and linked_id.startswith("LC_")):
            key = "FILE:" + path.name
            note = f"文件名 {name_id} 与现有原题链接 {linked_id} 不一致"
        else:
            key = name_id or linked_id or "FILE:" + path.name
            note = issue or ("来源与题号无法确认" if key.startswith("FILE:") else "")
        item = records[key]
        item["archive"].append(path)
        if identified:
            item["urls"].append(identified[1])
        if note:
            item["notes"].append(note)
        if key == "P225":
            item["notes"].append("官方题库未查到 P225，原文件中的链接待核实")

    for path in sorted(p for p in TEMPLATES.rglob("*") if p.suffix.lower() in EXTENSIONS):
        identified, _ = old_index.identify(path)
        if not identified:
            continue  # Generic templates and the existing candidate list remain separate.
        problem, url = identified
        item = records[problem]
        item["templates"].append(path)
        item["urls"].append(url)
        parts = path.relative_to(TEMPLATES).parts
        category = TOP.get(parts[0])
        topic = " / ".join(parts[1:-1]) or "综合"
        if category:
            item["topics"].append((category, topic))
        else:
            item["topics"].append((LEGACY_TOPICS.get(parts[1], "历史模板区"), topic))

    grouped = collections.defaultdict(list)
    evidence_counts = collections.Counter()
    review_files = 0
    for problem, item in records.items():
        topics = sorted(set(item["topics"]), key=lambda x: (CATEGORIES.index(x[0]) if x[0] in CATEGORIES else 99, x[1]))
        official = snapshot["luogu"].get(problem)
        cf = snapshot["codeforces"].get(problem)
        tags = luogu_tag_info(official["tags"], definitions) if official else []
        cf_tags = cf["tags"] if cf else []
        template_topics = [x for x in topics if x[0] in CATEGORIES]
        if template_topics:
            category, knowledge = template_topics[0]
            evidence = "templates 目录"
        elif problem in CODE_CLASSIFICATION:
            knowledge, category = CODE_CLASSIFICATION[problem]
            evidence = "本仓库代码/注释"
        elif tags:
            knowledge, category, _ = tags[0]
            evidence = "洛谷题目标签"
        elif cf_tags:
            known = [(x, CF_CATEGORY[x]) for x in cf_tags if x in CF_CATEGORY]
            if known:
                # More specific labels take precedence over generic implementation tags.
                known.sort(key=lambda x: (CF_TAG_PRIORITY.index(x[0]) if x[0] in CF_TAG_PRIORITY else len(CF_TAG_PRIORITY), x[0]))
                knowledge, category = known[0]
                evidence = "Codeforces 题目标签"
            else:
                category, knowledge, evidence = "待人工核实", "—", "标签无法映射"
        else:
            hint = next(((word, cat) for word, cat in NAME_HINTS if word.lower() in problem.lower() or any(word.lower() in p.stem.lower() for p in item["archive"])), None)
            if hint:
                knowledge, category = hint
                evidence = "文件名中的算法名称"
            else:
                category, knowledge, evidence = "待人工核实", "—", "缺少可靠算法归属"
        if item["notes"] and category == "待人工核实":
            knowledge = "；".join(sorted(set(item["notes"])))
        if category == "待人工核实":
            review_files += len(item["archive"])
        evidence_counts[evidence] += 1
        url = source_link(problem, next(iter(item["urls"]), None), snapshot)
        official_tags = [x[0] for x in tags] if tags else cf_tags
        grouped[category].append({
            "id": problem, "knowledge": knowledge, "official_tags": official_tags,
            "archive": sorted(set(item["archive"])), "templates": sorted(set(item["templates"])),
            "topics": topics, "url": url, "evidence": evidence,
            "notes": sorted(set(item["notes"])),
        })

    lines = [
        "# 全量算法练习清单", "",
        f"按当前仓库生成，覆盖 `洛谷/code` 的 **{len(archive_paths)} 份练习代码**，连同 `templates` 中已能确认题号的练习实现，共 **{len(records)} 个题目或待核实文件组**。同题多语言、多版本合并在一行。",
        "",
        "优先按 `templates` 现有专题归类；其余使用[洛谷题目标签](https://www.luogu.com.cn/problem/list)或 [Codeforces 官方标签](https://codeforces.com/apiHelp/methods)。官方标签描述题目可能涉及的知识点，**不证明本仓库这份代码实际使用该解法**。标签快照见[数据文件](练习题官方标签快照.json)，采集日期为 " + snapshot["captured_at"] + "。来源冲突写在备注中；完全没有算法内容的文件列在末尾，未猜测。",
        "",
        "已有较细的 `templates` 学习路线和一题多知识点关系，仍见[专题题单](算法学习题单.md)。此表为便于查找，给每题选一个主要归类；其余官方标签照列，不表示算法唯一。没有稳定 OJ 编号的比赛训练文件另见[练习赛代码索引](练习赛代码索引.md)，按场次归档。", "",
        "## 分类导航", "",
    ]
    for category in CATEGORIES:
        if grouped[category]:
            lines.append(f"- [{category}](#{category})：{len(grouped[category])} 项")
    lines.extend(["", "## 分类列表", ""])
    for category in CATEGORIES:
        entries = grouped[category]
        if not entries:
            continue
        lines.extend([f"### {category}", ""])
        by_knowledge = collections.defaultdict(list)
        for entry in entries:
            by_knowledge[entry["knowledge"]].append(entry)
        for knowledge, subset in sorted(by_knowledge.items(), key=lambda pair: (-len(pair[1]), pair[0])):
            lines.extend([
                f"#### {knowledge}（{len(subset)}）", "",
                "| 题号 / 文件 | 官方题目标签 | 练习代码 | templates 代码 | 归类依据 | 备注 |",
                "| --- | --- | --- | --- | --- | --- |",
            ])
            for entry in sorted(subset, key=lambda item: sort_key(item["id"])):
                label = entry["id"] if not entry["id"].startswith("FILE:") else entry["id"][5:]
                label = f"[{label}]({entry['url']})" if entry["url"] else label
                archive_cell = "、".join(file_link(p) for p in entry["archive"]) or "—"
                template_cell = "、".join(file_link(p) for p in entry["templates"]) or "—"
                tag_cell = "、".join(entry["official_tags"]) or "—"
                note_cell = "；".join(entry["notes"]).replace("|", "\\|") or "—"
                lines.append(f"| {label} | {tag_cell} | {archive_cell} | {template_cell} | {entry['evidence']} | {note_cell} |")
            lines.append("")
    OUTPUT.write_text("\n".join(lines), encoding="utf-8")
    all_archive = [p for group in grouped.values() for item in group for p in item["archive"]]
    assert len(all_archive) == len(archive_paths) and set(all_archive) == set(archive_paths)
    print("archive_files", len(archive_paths))
    print("problem_or_review_groups", len(records))
    print("categories", {key: len(grouped[key]) for key in CATEGORIES})
    print("evidence", dict(evidence_counts))
    print("review_files", review_files)
    print("output_bytes", OUTPUT.stat().st_size)
    training = collections.defaultdict(list)
    for path in TRAINING.rglob("*"):
        if path.is_file() and path.suffix.lower() in EXTENSIONS:
            training[path.parent.relative_to(TRAINING).as_posix()].append(path)
    training_lines = [
        "# 练习赛代码索引", "",
        f"共 **{sum(map(len, training.values()))}** 份代码，按原有比赛或训练目录归档。这里仅记录场次与文件，无法从 `A.cpp`、`t1.cpp` 等名称可靠判断 OJ 题号或算法时不补猜测。算法归类的练习见[全量算法练习清单](全量算法练习清单.md)。", "",
        "## 场次导航", "",
    ]
    for dirname in sorted(training):
        training_lines.append(f"- [{dirname}](#{re.sub(r'[^a-z0-9\u4e00-\u9fff-]', '', dirname.lower().replace('/', ''))})：{len(training[dirname])} 份")
    training_lines.append("")
    for dirname in sorted(training):
        training_lines.extend([f"## {dirname}", "", "、".join(file_link(p) for p in sorted(training[dirname])), ""])
    TRAINING_OUTPUT.write_text("\n".join(training_lines), encoding="utf-8")
    print("training_files", sum(map(len, training.values())))


if __name__ == "__main__":
    main()
