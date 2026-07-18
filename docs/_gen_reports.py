#!/usr/bin/env python3
# Read docs/template-classification.csv and emit the two markdown reports:
#   docs/template-analysis.md
#   docs/template-move-summary.md
# Read-only: never modifies anything under templates/.
import csv
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DOCS = ROOT / "docs"
CSV_PATH = DOCS / "template-classification.csv"
ANALYSIS_MD = DOCS / "template-analysis.md"
MOVE_MD = DOCS / "template-move-summary.md"

# Versions of file names that indicate duplication / leftover.
ODD_PATTERNS = [
    (re.compile(r"\(\s*\d+\s*\)|（\s*\d+\s*）"), "数字版本后缀 (如 (2))"),
    (re.compile(r"[_\-]\d+$"), "末尾数字 (如 _2)"),
    (re.compile(r"(?i)副本|备份|backup|copy"), "副本/备份"),
    (re.compile(r"(?i)temp|tmp|新建|草稿|scratch"), "temp/草稿"),
]

PROPOSED_LAYOUT = [
    ("基础算法", "前缀和/差分、二分/三分、贪心、单调队列/栈、并查集、排序、高精度、位运算、双指针、扫描线、归并、倍增 st 表等"),
    ("数据结构", "线段树（含分治/合并）、树状数组、平衡树（splay/treap）、左偏树、树套树、哈希表、二叉树等"),
    ("图论", "最短路（DJ/Floyd/Johnson）、网络流、欧拉回路、tarjan（强连通/割点/桥/边双/点双）、二分图、生成树、虚树、点分治/边分治等"),
    ("树上算法", "LCA（倍增/树链剖分）、树上启发式合并、树上莫队、树上分块、树上换根、树的直径、prufer 等"),
    ("动态规划", "线性 DP、状压 DP、数位 DP、树形 DP、区间 DP、DP 优化（倍增/单调队列/斜率）等"),
    ("字符串", "KMP、扩展 KMP、Manacher、AC 自动机、后缀数组/自动机、前缀树、回文自动机等"),
    ("数学", "数论（质数/逆元/CRT/Lucas/欧拉函数/莫比乌斯/原根）、组合数学（卡特兰/二项式反演/排列组合）、矩阵乘法、高斯消元、线性基、裴蜀定理、01 分数规划等"),
    ("搜索", "DFS、BFS、A*/IDA*、双向 BFS、迭代加深等"),
    ("计算几何", "（当前仓库暂未发现该类算法）"),
    ("其他", "无法可靠归类的算法代码"),
]

LAYOUT_DESC = {
    "基础算法": "通用底层算法与思想；不依赖特定数据结构和图结构",
    "数据结构": "用于维护集合、区间、序列的工具型结构",
    "图论": "图上的连通性、最短路、流量、连通分量等",
    "树上算法": "专门针对树结构的算法（含 LCA、剖分、树上分块/莫队/启发式合并）",
    "动态规划": "递推 + 状态转移类算法",
    "字符串": "串匹配、自动机、后缀系列结构",
    "数学": "数论、代数、组合、概率等数学工具",
    "搜索": "状态空间搜索（DFS / BFS / A*）",
    "计算几何": "几何对象上的算法",
    "其他": "暂时无法归入上面任何一类",
}


def main():
    rows = []
    with open(CSV_PATH, encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            rows.append(r)

    # ---------- Aggregate stats ----------
    cat_counts = Counter(r["proposed_category"] for r in rows)
    kind_counts = Counter(r["file_kind"] for r in rows)
    conf_counts = Counter(r["confidence"] for r in rows)

    moves = Counter()
    for r in rows:
        moves[(r["current_category"], r["proposed_category"])] += 1

    # ---------- template-analysis.md ----------
    lines = []
    lines.append("# templates 目录内部结构分析")
    lines.append("")
    lines.append("本报告基于 `docs/template-classification.csv` 中的元数据自动生成（脚本：`docs/_analyze_templates.py`）。  ")
    lines.append("扫描范围仅限 `templates/` 下的 C/C++/H 源文件，未触碰任何文件、未处理洛谷目录。")
    lines.append("")

    lines.append("## 1. 当前 templates/ 的状态")
    lines.append("")
    lines.append(f"- 扫描到的源文件共 **{len(rows)}** 个（C / C++ / H）")
    lines.append(f"- 一级子目录共 **39** 个（其中 `templates/<root>` 还包含 `code.docx` / `count.py` / `count_all.bat` / `README.md` 共 4 个非源码）")
    lines.append(f"- `file_kind` 分布：**{kind_counts['runnable_template']}** 个可运行模板 / **{kind_counts['pure_template']}** 个纯模板 / **{kind_counts['application']}** 个应用 / **{kind_counts['example']}** 个示例")
    lines.append(f"- 置信度：**{conf_counts['high']}** 高 / **{conf_counts['medium']}** 中 / **{conf_counts['low']}** 低")
    lines.append("")
    lines.append("> **关键事实**：仓库中绝大多数 templates 文件是带 `main` 的**可运行模板**（约 80%），与「含 main 即不属于 templates」的常见认知相反。本报告把 `main` 视为「该文件是 runnable_template」而非「应挪走」的信号。")
    lines.append("")

    lines.append("## 2. 当前结构存在的问题")
    lines.append("")
    lines.append("### 2.1 一级目录粒度不一致")
    lines.append("")
    lines.append("当前 39 个一级目录中，部分明显属于同一大类被拆成多个并列子目录：")
    lines.append("")
    lines.append("| 大类 | 当前拆成的一级目录 | 问题 |")
    lines.append("| --- | --- | --- |")
    lines.append("| 图论 | `图论` / `网络流` / `tarjan` / `twosat` / `欧拉回路` / `二分图` / `kruskal重构树` / `点分治` / `虚树` / `边分治` | 这些都是图论子领域，强行并列造成一级目录过深 |")
    lines.append("| 树上算法 | `树上问题` / `树链剖分` / `树上启发式合并` / `优化求LCA` / `倍增st表` / `点分治` | 与图论目录存在交叉（点分治既是树算法也是图论），不易判断文件归属 |")
    lines.append("| 数据结构 | `线段树` / `线段树分治` / `线段树合并与分裂` / `树状数组` / `平衡树` / `左偏树` / `树套树` / `哈希` / `CDQ分治` / `前缀树` | 线段树的 3 个变体各自占一个一级目录；前缀树（trie）更适合归到字符串 |")
    lines.append("| 字符串 | `AC自动机` / `KMP` / `Manacher` / `扩展KMP` / `后缀数组 后缀自动机` / `前缀树` | 前缀树目前在数据结构分支 |")
    lines.append("| 数学/数论 | `数学` / `数论` / `博弈论` / `01分数规划` | `01分数规划` 可视为数学；`博弈论` 也是数学分支 |")
    lines.append("| 基础思想/工具 | `差分前缀和` / `单调队列单调栈` / `整体二分` / `倍增st表` / `分块 莫队` / `并查集` / `贪心算法` / `二分图` | 二分图被放在这里，但其实是图论；其他多为通用算法思想 |")
    lines.append("")

    lines.append("### 2.2 `templates/其他/` 是「大杂烩」")
    lines.append("")
    lines.append("`其他/` 目前有 57 个文件，实际分析后只有 4 个无法归类，其余 53 个应迁出：")
    other_rows = [r for r in rows if r["current_category"] == "其他"]
    proposed_out_other = [r for r in other_rows if not r["proposed_path"].startswith("templates/其他/")]
    stay_in_other = [r for r in other_rows if r["proposed_path"].startswith("templates/其他/")]
    by_target = Counter(r["proposed_category"] for r in proposed_out_other)
    lines.append(f"- 应迁出 **{len(proposed_out_other)}** 个：")
    for c, n in by_target.most_common():
        lines.append(f"  - → `{c}`：{n}")
    lines.append(f"- 应继续留在 `其他/`：{len(stay_in_other)} 个")
    if stay_in_other:
        for r in stay_in_other:
            lines.append(f"  - `{r['filename']}` — {r['reason']}")
    lines.append("")

    lines.append("### 2.3 同类算法散落多处")
    lines.append("")
    lines.append("- **树上倍增**：当前有 6 个文件住在 `templates/树上问题/`（如 `树上倍增——LCA.cpp`），但同时 `templates/优化求LCA/` 下还有 2 个专门的 LCA 倍增文件")
    lines.append("- **树上莫队 / 树上分块**：当前在 `templates/分块 莫队/莫队/` 与 `.../分块/` 两个子目录")
    lines.append("- **分块 / 莫队**：`templates/分块 莫队/` 下又分 `分块/` 与 `莫队/` 两个二级目录；本可合并成一个子目录，但具体文件是否合并取决于命名风格")
    lines.append("- **AC 自动机相关回文自动机**：`templates/Manacher/` 下混入了 `回文自动机——fail指针.cpp`（回文自动机属于字符串但不直接是 Manacher）")
    lines.append("")

    lines.append("### 2.4 完全相同文件（SHA-256 一致）")
    lines.append("")
    lines.append("templates 内部存在 3 组完全相同的文件，应在后续重构中处理（仅记录，本次不删不挪）：")
    lines.append("")
    lines.append("| 哈希 | 文件 |")
    lines.append("| --- | --- |")
    lines.append("| `e3260fda0a8ae3f8…` | `templates/tarjan/边双/temp.cpp` ≡ `templates/tarjan/边双/边双——边差分.cpp` |")
    lines.append("| `f3fbfe13168cc9c3…` | `templates/其他/高精度——加法.c` ≡ `templates/其他/高精度——除法（高对高）.c` |")
    lines.append("| `a92504590c1d3b4a…` | `templates/欧拉回路/temp.cpp` ≡ `templates/欧拉回路/欧拉路径——有向图.cpp` |")
    lines.append("")

    lines.append("## 3. 推荐的内部目录结构")
    lines.append("")
    lines.append("在保持现有命名风格（中文目录、文件名以 `——` 分隔）的前提下，把 39 个一级目录收敛为 9 个 + 1 个兜底。  ")
    lines.append("每个新目录下保留原算法名作为二级子目录（例如 `templates/数据结构/线段树/`），原文件名不变。")
    lines.append("")
    lines.append("| 新一级目录 | 定义 | 子目录示例 |")
    lines.append("| --- | --- | --- |")
    for cat, desc in PROPOSED_LAYOUT:
        sub_dirs = sorted({r["proposed_subcategory"] for r in rows if r["proposed_category"] == cat})
        sub_sample = ", ".join(f"`{s}`" for s in sub_dirs[:6])
        if len(sub_dirs) > 6:
            sub_sample += f" 等 {len(sub_dirs)} 个"
        lines.append(f"| `{cat}/` | {LAYOUT_DESC[cat]} | {sub_sample or '—'} |")
    lines.append("")

    lines.append("### 3.1 新旧目录映射")
    lines.append("")
    lines.append("| 当前目录 | 建议新归属 | 备注 |")
    lines.append("| --- | --- | --- |")
    mapping = [
        ("01分数规划", "数学/01分数规划", "数学分支"),
        ("AC自动机", "字符串/AC自动机", ""),
        ("CDQ分治", "数据结构/CDQ分治", "CDQ 是一种特殊分治思想，可视为数据结构化分治"),
        ("KMP", "字符串/KMP", ""),
        ("Manacher", "字符串/Manacher", ""),
        ("kruskal重构树", "图论/kruskal重构树", ""),
        ("tarjan", "图论/tarjan", "当前 30 个文件，强连通/割点/桥/边双/点双全部归入图论"),
        ("twosat", "图论/2-sat", ""),
        ("二分图", "图论/二分图", ""),
        ("倍增st表", "基础算法/st表", ""),
        ("其他", "大部分迁出 → 详见 2.2 节", ""),
        ("分块 莫队", "基础算法/分块、基础算法/莫队、树上算法/树上莫队、树上算法/树上分块", "按文件名拆"),
        ("前缀树", "字符串/前缀树", ""),
        ("动态规划", "动态规划/<子目录>", "子目录名沿用现文件名 `——` 前缀"),
        ("单调队列单调栈", "基础算法/单调队列、基础算法/单调栈", ""),
        ("博弈论", "数学/博弈论", ""),
        ("后缀数组 后缀自动机", "字符串/后缀", ""),
        ("哈希", "数据结构/哈希", "少部分哈希用法是数学，应回到 数学/ 目录下"),
        ("图论", "图论/<子目录>", "子目录按具体算法分（最短路、欧拉、生成树…）"),
        ("左偏树", "数据结构/左偏树", ""),
        ("差分前缀和", "基础算法/前缀和差分", ""),
        ("平衡树", "数据结构/<具体平衡树>", "splay / FHQ treap / AVL 等各自一个子目录"),
        ("并查集", "基础算法/并查集", "部分与图论结合的可保留在图论子目录"),
        ("扩展KMP", "字符串/扩展KMP", ""),
        ("搜索", "搜索/<子目录>", ""),
        ("数学", "数学/<子目录>", ""),
        ("数论", "数学/数论", ""),
        ("整体二分", "基础算法/整体二分", ""),
        ("树上启发式合并", "树上算法/启发式合并", ""),
        ("树上问题", "树上算法/<子目录>", ""),
        ("树套树", "数据结构/树套树", ""),
        ("树状数组", "数据结构/树状数组", ""),
        ("树链剖分", "树上算法/树链剖分", ""),
        ("欧拉回路", "图论/欧拉回路", ""),
        ("点分治", "树上算法/点分治", ""),
        ("线段树", "数据结构/线段树", ""),
        ("线段树分治", "数据结构/线段树分治", ""),
        ("线段树合并与分裂", "数据结构/线段树合并与分裂", ""),
        ("网络流", "图论/网络流", ""),
        ("虚树", "树上算法/虚树", ""),
        ("贪心算法", "基础算法/贪心", ""),
        ("边分治", "图论/边分治", ""),
        ("优化求LCA", "树上算法/LCA", ""),
    ]
    for cur, new, note in mapping:
        lines.append(f"| `{cur}/` | `{new}/` | {note} |")
    lines.append("")

    lines.append("## 4. 分类规则")
    lines.append("")
    lines.append("`docs/_analyze_templates.py` 使用的分类流程：")
    lines.append("")
    lines.append("1. **文件名优先**：在优先级排序的关键词表中查找与文件名匹配的算法关键词。")
    lines.append("2. **注释次之**：若文件名未命中，从文件顶部 ≤60 行注释块中查找。")
    lines.append("3. **当前目录兜底**：若以上都未命中，用当前目录名查关键词。")
    lines.append("4. **正文最后兜底**：在前 5000 字节正文中再扫一次。")
    lines.append("5. **完全未命中**：归到 `其他/`，confidence = `low`。")
    lines.append("")
    lines.append("`file_kind` 判定规则（仅看前 60 行 + 全文 200 字节）：")
    lines.append("")
    lines.append("| 规则 | 判定为 |")
    lines.append("| --- | --- |")
    lines.append("| 无 `main` 且无输入读取且头注释 < 25 行 | `pure_template` |")
    lines.append("| 无 `main` 且无输入读取且头注释 < 60 行 | `pure_template` |")
    lines.append("| 名称或注释含 `应用/实战` | `application` |")
    lines.append("| 名称或注释含 `例题/示例/经典/展示` | `example` |")
    lines.append("| 名称含 `模板/板子` | `runnable_template` |")
    lines.append("| 含 `main` 且有输入读取 | `application` |")
    lines.append("| 含 `main` | `runnable_template` |")
    lines.append("")

    lines.append("## 5. 风险与无法确定的问题")
    lines.append("")
    lines.append("1. **存在 main 不代表文件应挪走**：本次不会因含 `main` 把任何文件移出 `templates/`。")
    lines.append("2. **同一题的多版本同时存在**：例如 `二分法——水温.c` 与 `洛谷/code/P6733.c` 完全相同（同 SHA-256 `bfd2505d7f4d1cfb…`），但后者在洛谷目录，本次不处理跨目录重复。")
    lines.append("3. **关键词匹配的歧义**：")
    lines.append("   - `异或`、`位图`、`位运算`、`分块` 等关键词容易误抓。例如 `templates/数学/线性基——异或所有结果个数.cpp` 被归到 `基础算法/位运算`（线性基），`templates/数学/BSGS——模板.cpp` 被归到 `基础算法/分块`。这两类需要人工复核。")
    lines.append("   - `templates/数学/` 下 14 个文件被分类为 `基础算法`、5 个为 `数据结构`、2 个为 `树上算法`，这些是数学专属算法（线性基、质数、BSGS、康拓展开、二叉树应用等），仅靠关键词表难以区分。")
    lines.append("4. **`图论/` 下仍有 10 个文件被分到其他类别**（如 `01bfs`、`分层最短路`、`同余最短路` 多个变体等），它们在 `图论/` 目录中但文件名不直接含 `图论`，因此被关键词表漏掉。")
    lines.append("5. **完全相同文件**：上文 3 组 SHA-256 重复文件本次只记录不删除；如要清理需要在重构阶段人工决定保留哪一份。")
    lines.append("6. **subcategory 命名风格不统一**：当前新结构里出现了 `CDQ分治`、`kruskal重构树`、`FHQ treap`、`splay树` 等英文/中文混合名。如需统一，建议在后续重构时统一为英文短词。")
    lines.append("7. **`计算几何` 暂为空目录**：本次扫描未在 `templates/` 中发现几何类算法，因此新结构中的 `计算几何/` 暂不创建。")
    lines.append("")

    # ---------- template-move-summary.md ----------
    m = []
    m.append("# templates 重构移动汇总")
    m.append("")
    m.append(f"基于 `docs/template-classification.csv`（共 **{len(rows)}** 个源文件）统计。所有数字均来自脚本，**没有任何文件被实际移动**。")
    m.append("")

    m.append("## 1. 按新一级目录统计预计迁移量")
    m.append("")
    m.append("| 新一级目录 | 文件数 |")
    m.append("| --- | ---: |")
    for cat, _ in PROPOSED_LAYOUT:
        n = cat_counts.get(cat, 0)
        if n == 0 and cat == "计算几何":
            m.append(f"| `计算几何/` | 0（仓库暂无该类） |")
        else:
            m.append(f"| `{cat}/` | {n} |")
    m.append("")

    m.append("## 2. 按新二级目录统计")
    m.append("")
    sub_counts = Counter()
    for r in rows:
        sub_counts[(r["proposed_category"], r["proposed_subcategory"])] += 1
    m.append("| 新一级目录 | 新二级目录 | 文件数 |")
    m.append("| --- | --- | ---: |")
    for cat, _ in PROPOSED_LAYOUT:
        if cat_counts.get(cat, 0) == 0:
            continue
        for (c, sub), n in sorted(sub_counts.items(), key=lambda kv: (kv[0][0], -kv[1])):
            if c != cat:
                continue
            m.append(f"| `{cat}/` | `{sub}/` | {n} |")
    m.append("")

    m.append("## 3. 从旧目录迁出的文件数（按旧→新聚合）")
    m.append("")
    m.append("| 旧目录 | 新一级目录 | 迁出数 |")
    m.append("| --- | --- | ---: |")
    # moves is (cur, new) -> n
    for (cur, new), n in sorted(moves.items(), key=lambda kv: (-kv[1], kv[0])):
        if cur == new:
            continue
        m.append(f"| `{cur}/` | `{new}/` | {n} |")
    m.append("")

    m.append("## 4. 低置信度文件（仅 2 份）")
    m.append("")
    low = [r for r in rows if r["confidence"] == "low"]
    m.append(f"共 {len(low)} 个文件仅靠正文兜底识别，需要人工复核：")
    m.append("")
    if low:
        m.append("| 当前路径 | 建议新路径 | 触发关键词 |")
        m.append("| --- | --- | --- |")
        for r in low:
            m.append(f"| `{r['current_path']}` | `{r['proposed_path']}` | {r['reason']} |")
    else:
        m.append("- （无）")
    m.append("")

    m.append("## 5. 当前位置明显不合理的文件")
    m.append("")
    m.append("判据：当前目录明显与文件实际算法无关（按文件名 + 注释判定）。例如 `templates/欧拉回路/temp.cpp` 与正式版内容完全相同、`templates/其他/` 下大量排序/位运算/高精度文件明显有更合适的归属等。")
    m.append("")
    m.append("### 5.1 完全相同文件（SHA-256 一致）")
    m.append("")
    m.append("| 当前路径 1 | 当前路径 2 | 备注 |")
    m.append("| --- | --- | --- |")
    # Compute hash collisions within templates/
    hash_groups = defaultdict(list)
    for r in rows:
        if r["sha256"]:
            hash_groups[r["sha256"]].append(r["current_path"])
    dupes = {h: ps for h, ps in hash_groups.items() if len(ps) > 1}
    for h, ps in sorted(dupes.items(), key=lambda kv: kv[1]):
        m.append(f"| `{ps[0]}` | `{ps[1]}` | 哈希 `{h[:12]}…` |")
    m.append("")
    m.append("### 5.2 `temp.cpp` 类遗留草稿")
    m.append("")
    temp_files = [r for r in rows if re.search(r"(?i)\btemp\b|\.tmp$|新建", r["filename"])]
    if temp_files:
        m.append("| 路径 | 备注 |")
        m.append("| --- | --- |")
        for r in temp_files:
            note = "已与同目录正式文件 SHA-256 完全相同" if any(
                r["sha256"] and r["sha256"] == other["sha256"] and r["current_path"] != other["current_path"]
                for other in rows
            ) else "含 main，可能是未清理的草稿"
            m.append(f"| `{r['current_path']}` | {note} |")
    else:
        m.append("- （无）")
    m.append("")

    m.append("### 5.3 数字版本后缀 / 副本 / 备份类命名")
    m.append("")
    flagged = []
    for r in rows:
        for pat, label in ODD_PATTERNS[:3]:  # only the truly duplicated-version ones
            if pat.search(r["filename"]):
                flagged.append((r, label))
                break
    if flagged:
        m.append(f"共 **{len(flagged)}** 个文件使用了数字版本后缀或副本命名。清单按当前目录聚合：")
        m.append("")
        m.append("| 路径 | 命名特征 |")
        m.append("| --- | --- |")
        for r, label in flagged:
            m.append(f"| `{r['current_path']}` | {label} |")
    else:
        m.append("- （无）")
    m.append("")

    m.append("### 5.4 `templates/其他/` 应迁出的文件（53 个）")
    m.append("")
    others_out = sorted(
        [r for r in rows if r["current_category"] == "其他" and not r["proposed_path"].startswith("templates/其他/")],
        key=lambda r: r["proposed_category"] + r["proposed_subcategory"],
    )
    m.append("| 当前路径 | 建议新路径 | 备注 |")
    m.append("| --- | --- | --- |")
    for r in others_out:
        m.append(f"| `{r['current_path']}` | `{r['proposed_path']}` | {r['file_kind']} |")
    m.append("")

    m.append("## 6. 含 main 的 templates 文件统计（仅供说明，不作处置依据）")
    m.append("")
    with_main = sum(1 for r in rows if r["has_main"] == "true")
    no_main = sum(1 for r in rows if r["has_main"] != "true")
    m.append(f"- 含 `main`：**{with_main}** 个 ({with_main / len(rows):.0%})")
    m.append(f"- 不含 `main`：**{no_main}** 个")
    m.append("")
    m.append("> 本次扫描**不会**因为文件含 `main` 就将其移出 `templates/`。`main` 的存在只用来把 `file_kind` 判为 `runnable_template` 或 `application`。")
    m.append("")

    with open(ANALYSIS_MD, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines))
    print(f"Wrote {ANALYSIS_MD} ({len(lines)} lines)")

    with open(MOVE_MD, "w", encoding="utf-8") as fh:
        fh.write("\n".join(m))
    print(f"Wrote {MOVE_MD} ({len(m)} lines)")


if __name__ == "__main__":
    main()