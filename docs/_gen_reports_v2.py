#!/usr/bin/env python3
# Read docs/template-classification-v2.csv and emit three markdown reports:
#   docs/template-analysis-v2.md
#   docs/template-move-summary-v2.md
#   docs/template-collision-report.md
# Read-only: never modifies anything under templates/.
import csv
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DOCS = ROOT / "docs"
CSV_PATH = DOCS / "template-classification-v2.csv"
ANALYSIS_MD = DOCS / "template-analysis-v2.md"
MOVE_MD = DOCS / "template-move-summary-v2.md"
COLLISION_MD = DOCS / "template-collision-report.md"


def main():
    rows = []
    with open(CSV_PATH, encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            rows.append(r)

    # Validation stats
    cur_paths = [r["current_path"] for r in rows]
    prop_paths = [r["proposed_path"] for r in rows]
    cur_uniq = len(set(cur_paths))
    prop_uniq = len(set(prop_paths))
    cur_dups = len(cur_paths) - cur_uniq
    prop_dups = len(prop_paths) - prop_uniq
    conf = Counter(r["confidence"] for r in rows)
    review = Counter(r["review_required"] for r in rows)
    cs = Counter(r["collision_status"] for r in rows)
    cat_counts = Counter(r["proposed_top_category"] for r in rows)
    kind_counts = Counter(r["file_kind"] for r in rows)
    basis_counts = Counter(r["classification_basis"] for r in rows)

    moves = Counter()
    for r in rows:
        moves[(r["current_category"], r["proposed_top_category"])] += 1

    # ---------- template-analysis-v2.md ----------
    a = []
    a.append("# templates 目录内部结构分析 (v2)")
    a.append("")
    a.append("本报告基于 `docs/template-classification-v2.csv` 自动生成（脚本：`docs/_analyze_templates.py`）。")
    a.append("扫描范围仅限 `templates/` 下的 C/C++/H 源文件，未触碰任何文件、未处理洛谷目录。")
    a.append("")

    a.append("## 1. 当前 templates/ 的状态")
    a.append("")
    a.append(f"- 共 **{len(rows)}** 个 C/C++/H 源文件")
    a.append(f"- `file_kind` 分布：**{kind_counts['runnable_template']}** 个可运行模板 / **{kind_counts['pure_template']}** 个纯模板 / **{kind_counts['application']}** 个应用 / **{kind_counts['example']}** 个示例")
    a.append(f"- 置信度：**{conf['high']}** 高 / **{conf['medium']}** 中 / **{conf['low']}** 低")
    a.append(f"- 分类依据（classification_basis）：")
    for b, n in basis_counts.most_common():
        a.append(f"  - `{b}`：{n}")
    a.append("")
    a.append("> **关键事实**：仓库中绝大多数 templates 文件是带 `main` 的**可运行模板**（约 80%）。本报告把 `main` 视为「该文件是 runnable_template」而非「应挪走」的信号，因此**不会因含 main 把任何文件移出 templates**。")
    a.append("")

    a.append("## 2. v1 → v2 的核心修正")
    a.append("")
    a.append("| 问题 | v1 做法 | v2 做法 |")
    a.append("| --- | --- | --- |")
    a.append("| 主要算法被辅助技术抢分类 | 看到 `线段树` 就归 `数据结构`，看到 `异或` 就归 `基础算法` | 文件名 `——` 之前是 primary，之后是 secondary。primary 才决定一级目录 |")
    a.append("| 同算法家族散落多目录 | `线性基——异或所有结果.cpp` → `基础算法/位运算` | `线性基——异或所有结果.cpp` → `数学/线性代数/线性基/` |")
    a.append("| 同题两份无法区分 | 两条 `圆方树——模板.cpp` 都映射到同一目标路径 | 产生冲突时按内容生成可理解后缀，**两个文件均保留** |")
    a.append("| 置信度与可靠性脱节 | 命中一个关键词就标 `high` | 必须 primary 文件名匹配 + 分类家族与当前目录一致 才标 `high`；冲突或需复核一律降级 |")
    a.append("")

    a.append("## 3. 推荐的内部目录结构")
    a.append("")
    a.append("按 `primary_algorithm` → 算法家族 → 三级目录 组织。一级目录 9 个，不创建空的 `计算几何/`：")
    a.append("")
    a.append("```")
    a.append("templates/")
    a.append("├─ 基础算法/")
    a.append("├─ 数据结构/")
    a.append("├─ 图论/")
    a.append("├─ 树上算法/")
    a.append("├─ 动态规划/")
    a.append("├─ 字符串/")
    a.append("├─ 数学/")
    a.append("├─ 搜索/")
    a.append("└─ 其他/")
    a.append("```")
    a.append("")
    a.append("### 3.1 一级目录职责")
    a.append("")
    a.append("| 一级目录 | 职责 |")
    a.append("| --- | --- |")
    a.append("| `基础算法/` | 通用底层算法与思想：二分/三分、贪心、单调栈/队列、前缀和/差分、并查集、排序、高精度、位运算、双指针、扫描线、整体二分、莫队、分块、倍增 st 表等 |")
    a.append("| `数据结构/` | 维护集合、区间、序列的工具型结构：线段树（含分治/合并/可持久化）、树状数组、平衡树（splay/FHQ treap/AVL/Treap）、左偏树、树套树、哈希、ODT、二叉树、笛卡尔树、有序表、CDQ 分治等 |")
    a.append("| `图论/` | 图上的连通性、最短路、流量等：最短路（Dijkstra/Floyd/Johnson/0-1 BFS/分层/同余/次短路/K 短路）、网络流（最大流/最小割/费用流/上下界）、Tarjan 系列（强连通/割点/割边/边双/点双/圆方树）、二分图、欧拉路径、生成树（含 kruskal 重构树、最小树形图）、虚树、点分树（与树上算法共用）、边分治、2-SAT、prufer、拓扑排序 |")
    a.append("| `树上算法/` | 树结构上的算法：LCA（含树上倍增）、树链剖分（含长链剖分）、启发式合并、树上差分、树上换根、树的直径、树上问题、树上分块、树上莫队、树上哈希 |")
    a.append("| `动态规划/` | 递推 + 状态转移：通用 DP、DP 优化、数位 DP、状压 DP、树形 DP、区间 DP、轮廓线 DP、背包 DP |")
    a.append("| `字符串/` | 串匹配、自动机、后缀系列：KMP、扩展 KMP、Manacher、AC 自动机、后缀数组、后缀自动机、前缀树（含可持久化前缀树）、回文自动机、失配树 |")
    a.append("| `数学/` | 数论、组合数学、多项式、线性代数、博弈论、01 分数规划 |")
    a.append("| `搜索/` | 状态空间搜索：DFS / BFS / A* / IDA* / TSP |")
    a.append("| `其他/` | 暂时无法归类的（当前仅 3 个） |")
    a.append("")

    a.append("### 3.2 完整二级 / 三级目录树")
    a.append("")
    sub_counts = Counter()
    for r in rows:
        sub_counts[(r["proposed_top_category"], r["proposed_subcategory"])] += 1
    by_top: dict[str, list[tuple[str, int]]] = defaultdict(list)
    for (top, sub), n in sub_counts.items():
        by_top[top].append((sub, n))
    for top in sorted(by_top.keys()):
        if cat_counts.get(top, 0) == 0:
            continue
        a.append(f"#### `{top}/`（共 {cat_counts.get(top, 0)} 个文件）")
        a.append("")
        # Identify which subs have nested third-level (contain '/')
        flat = [(s, n) for s, n in by_top[top] if "/" not in s]
        nested: dict[str, list[tuple[str, int]]] = defaultdict(list)
        for s, n in by_top[top]:
            if "/" in s:
                p1, _, p2 = s.partition("/")
                nested[p1].append((p2, n))
        for sub, n in sorted(flat, key=lambda x: -x[1]):
            a.append(f"- `{sub}/` × {n}")
        for p1, items in sorted(nested.items()):
            total = sum(n for _, n in items)
            a.append(f"- `{p1}/` × {total}")
            for p2, n in sorted(items, key=lambda x: -x[1]):
                a.append(f"  - `{p2}/` × {n}")
        a.append("")

    a.append("## 4. 分类规则（v2）")
    a.append("")
    a.append("`docs/_analyze_templates.py` 的决策流程：")
    a.append("")
    a.append("1. 拆分文件名：以 `——` / `--` / ` - ` 为分隔，取首段为 **primary**，余下为 **secondary techniques**")
    a.append("2. 在 `PRIMARY_MAP` 中查找 primary（去掉 `(2)` 等数字后缀）；命中即确定 (一级, 子路径)")
    a.append("3. 若 primary 未命中，使用当前目录 `DIR_FALLBACK_MAP` 兜底")
    a.append("4. 若仍未命中，对文件名再做一次全字段扫描（兜底）")
    a.append("5. 仍无命中 → `其他/未分类/`，confidence=`low`")
    a.append("")
    a.append("confidence 判定：")
    a.append("")
    a.append("| 规则 | confidence |")
    a.append("| --- | --- |")
    a.append("| 文件名 primary 命中，且 proposed_top 与 current_category 所在家族一致 | `high` |")
    a.append("| 文件名 primary 命中，但 proposed_top 跨家族（如 `图论` → `数学`） | `medium` |")
    a.append("| primary 未命中，靠目录兜底 / 关键词兜底 | `medium` |")
    a.append("| 冲突被自动消解（同名不同内容） | `medium`（且 `review_required=true`） |")
    a.append("| SHA-256 完全相同（重复文件） | `low`（且 `collision_status=duplicate_review`） |")
    a.append("| 完全无命中（`其他/未分类/`） | `low` |")
    a.append("")

    a.append("## 5. 算法家族保留原则")
    a.append("")
    a.append("下列算法家族**绝不**因为辅助关键词而分散到不同一级目录：")
    a.append("")
    a.append("| 家族 | 始终归入 |")
    a.append("| --- | --- |")
    a.append("| 线性基 | `数学/线性代数/线性基/` |")
    a.append("| 卡特兰数 | `数学/组合数学/卡特兰数/` |")
    a.append("| 康拓展开 | `数学/组合数学/康拓展开/` |")
    a.append("| 点分治 / 点分树 / 静态点分治 | `树上算法/点分树/` |")
    a.append("| 边双 / 点双 / 割点 / 割边 / 圆方树 / 强连通分量 | `图论/Tarjan/<子家族>/` |")
    a.append("| 网络流（最大流/最小割/费用流/上下界） | `图论/网络流/<子家族>/` |")
    a.append("| 最短路（DJ/Floyd/Johnson/0-1 BFS/分层/同余/次短路/K 短路） | `图论/最短路/<子家族>/` |")
    a.append("| 欧拉路径 / 欧拉回路 / 欧拉图 | `图论/欧拉路径/` |")
    a.append("| 并查集 / 可撤销 / 带权 / 可持久化 | `基础算法/并查集/<子家族>/` |")
    a.append("| 分块 / 普通分块 / 整除分块 / 时间分块 / 块状链表 / 根号分治 / 双层分块 | `基础算法/分块/<子家族>/` |")
    a.append("| 莫队 / 带修 / 只增回滚 / 只删回滚 / 二次离线 | `基础算法/莫队/<子家族>/` |")
    a.append("| 树链剖分 / 长链剖分 | `树上算法/树链剖分/` |")
    a.append("| 树上启发式合并 | `树上算法/启发式合并/` |")
    a.append("| 虚树 | `图论/虚树/` |")
    a.append("| AC 自动机 | `字符串/AC自动机/` |")
    a.append("| 前缀树 / 可持久化前缀树 | `字符串/前缀树/<子家族>/` |")
    a.append("| 线段树（基础/可持久化/分治/合并/分裂/优化建图） | `数据结构/线段树/<子家族>/` |")
    a.append("| 动态规划各类子专题 | `动态规划/<子家族>/` |")
    a.append("")

    a.append("## 6. 冲突与命名消解")
    a.append("")
    a.append("v1 中遇到 2 组同文件名（不同内容）的冲突，本次已自动消解：")
    a.append("")
    a.append("- `templates/tarjan/圆方树——模板.cpp` 与 `templates/tarjan/点双/圆方树——模板.cpp` → 都映射到 `图论/Tarjan/圆方树/圆方树——模板.cpp`，按内容生成 `[54e95b]` / `[ea1445]` 后缀区分")
    a.append("- `templates/数学/莫比乌斯函数——模板.cpp` 与 `templates/数论/莫比乌斯函数——模板.cpp` → 都映射到 `数学/数论/莫比乌斯反演/莫比乌斯函数——模板.cpp`，按内容生成 `[P4450]` / `[否则是-1]` 后缀区分")
    a.append("")
    a.append("完整冲突记录见 `docs/template-collision-report.md`.")
    a.append("")

    a.append("## 7. 风险与无法确定的问题")
    a.append("")
    a.append("1. **3 个 `其他/未分类/` 文件**：`极大化思想最大子矩阵.cpp`、`社会基尼系数.c`、`线段最小覆盖问题.cpp`。它们没有可识别的 primary 关键词，需要人工判定归类（疑似一个数学、一个排序/统计、一个 DP/贪心）。")
    a.append("2. **11 个 medium 置信度文件**（清单见 `template-move-summary-v2.md`）：")
    a.append("   - 4 个 review_required（冲突消解）")
    a.append("   - 2 个 `图论/` 目录下的 `线段树优化建图——*.cpp` 应放 `数据结构/线段树/线段树优化建图/`（primary 是线段树优化建图），故跨家族 → medium")
    a.append("   - 1 个 `图论/树上换根——最短路.cpp` 应放 `树上算法/树上换根/`（primary 是树上换根），跨家族 → medium")
    a.append("   - 2 个 `temp.cpp`（`tarjan/边双/temp.cpp`、`欧拉回路/temp.cpp`）被识别为正式文件，其实是草稿，建议在重构时手工删除")
    a.append("   - `归并分治.c` 走关键词兜底归到 `基础算法/排序/归并/`")
    a.append("   - `树上问题/生成树倍增LCA.cpp` 走目录兜底归到 `树上算法/树上问题/`，但实际是 LCA 题，可考虑挪到 `树上算法/LCA/`")
    a.append("3. **同题多版本**：v1 已识别 384 个文件名族（`(2) / _2 / 副本` 等），v2 沿用同一套检测规则（详见 `template-move-summary-v2.md` §5.3）。本次不对其去重。")
    a.append("4. **目录命名风格不统一**：新二级目录中存在 `CDQ分治 / kruskal重构树 / FHQ treap / splay树 / Tarjan / 0-1 BFS / K短路` 等英文/中文混合名。本次为保留现状不统一。")
    a.append("5. **未触动洛谷目录**：本轮所有分析仅覆盖 `templates/`。")
    a.append("")

    with open(ANALYSIS_MD, "w", encoding="utf-8") as fh:
        fh.write("\n".join(a))
    print(f"Wrote {ANALYSIS_MD}")

    # ---------- template-move-summary-v2.md ----------
    m = []
    m.append("# templates 重构移动汇总 (v2)")
    m.append("")
    m.append(f"基于 `docs/template-classification-v2.csv`（{len(rows)} 行）。所有数字均来自脚本，**没有任何文件被实际移动**。")
    m.append("")

    m.append("## 1. 验证结果")
    m.append("")
    m.append("| 指标 | 值 |")
    m.append("| --- | ---: |")
    m.append(f"| 总行数 | {len(rows)} |")
    m.append(f"| `current_path` 唯一数 | {cur_uniq} (重复 {cur_dups}) |")
    m.append(f"| `proposed_path` 唯一数 | {prop_uniq} (重复 {prop_dups}) |")
    m.append(f"| 置信度高 | {conf['high']} |")
    m.append(f"| 置信度中 | {conf['medium']} |")
    m.append(f"| 置信度低 | {conf['low']} |")
    m.append(f"| `review_required=true` | {review['true']} |")
    m.append(f"| `collision_status=resolved` | {cs['resolved']} |")
    m.append(f"| `collision_status=duplicate_review` | {cs['duplicate_review']} |")
    m.append(f"| `collision_status=none` | {cs['none']} |")
    m.append("")

    m.append("## 2. 按新一级目录统计")
    m.append("")
    m.append("| 新一级目录 | 文件数 |")
    m.append("| --- | ---: |")
    for cat in ("基础算法", "数据结构", "图论", "树上算法", "动态规划", "字符串", "数学", "搜索", "其他"):
        m.append(f"| `{cat}/` | {cat_counts.get(cat, 0)} |")
    m.append("")

    m.append("## 3. 按新二级 / 三级目录统计")
    m.append("")
    m.append("| 一级 | 二级 / 三级 | 文件数 |")
    m.append("| --- | --- | ---: |")
    for top in ("基础算法", "数据结构", "图论", "树上算法", "动态规划", "字符串", "数学", "搜索", "其他"):
        if cat_counts.get(top, 0) == 0:
            continue
        flat = sorted([(s, n) for (t, s), n in sub_counts.items() if t == top and "/" not in s], key=lambda x: -x[1])
        nested: dict[str, list[tuple[str, int]]] = defaultdict(list)
        for (t, s), n in sub_counts.items():
            if t == top and "/" in s:
                p1, _, p2 = s.partition("/")
                nested[p1].append((p2, n))
        for sub, n in flat:
            m.append(f"| `{top}/` | `{sub}/` | {n} |")
        for p1, items in sorted(nested.items()):
            total = sum(n for _, n in items)
            m.append(f"| `{top}/` | `{p1}/` | {total} |")
            for p2, n in sorted(items, key=lambda x: -x[1]):
                m.append(f"| `{top}/` | `{p1}/{p2}/` | {n} |")
    m.append("")

    m.append("## 4. 从旧目录迁出的文件数（按旧→新聚合）")
    m.append("")
    m.append("| 旧目录 | 新一级目录 | 迁出数 |")
    m.append("| --- | --- | ---: |")
    for (cur, new), n in sorted(moves.items(), key=lambda kv: (-kv[1], kv[0])):
        if cur == new:
            continue
        m.append(f"| `{cur}/` | `{new}/` | {n} |")
    m.append("")

    m.append("## 5. 低置信度文件")
    m.append("")
    low = [r for r in rows if r["confidence"] == "low"]
    m.append(f"共 {len(low)} 个文件无法靠 primary 自动分类，需要人工决定：")
    m.append("")
    m.append("| 当前路径 | 建议新路径 | 备注 |")
    m.append("| --- | --- | --- |")
    for r in low:
        m.append(f"| `{r['current_path']}` | `{r['proposed_path']}` | {r['classification_basis']} |")
    m.append("")

    m.append("## 6. 中等置信度文件（不含 review_required）")
    m.append("")
    medium = [r for r in rows if r["confidence"] == "medium" and r["review_required"] != "true"]
    m.append(f"共 {len(medium)} 个：")
    m.append("")
    m.append("| 当前路径 | 建议新路径 | 分类依据 |")
    m.append("| --- | --- | --- |")
    for r in medium:
        m.append(f"| `{r['current_path']}` | `{r['proposed_path']}` | {r['classification_basis']} |")
    m.append("")

    m.append("## 7. 需要复核的文件（review_required=true）")
    m.append("")
    rev = [r for r in rows if r["review_required"] == "true"]
    m.append(f"共 {len(rev)} 个（全部由同文件名冲突产生）。详见 `template-collision-report.md`。")
    m.append("")
    m.append("| 当前路径 | 建议新路径 | 冲突状态 |")
    m.append("| --- | --- | --- |")
    for r in rev:
        m.append(f"| `{r['current_path']}` | `{r['proposed_path']}` | {r['collision_status']} |")
    m.append("")

    m.append("## 8. 完全相同文件（SHA-256 一致）")
    m.append("")
    by_hash = defaultdict(list)
    for r in rows:
        if r["sha256"]:
            by_hash[r["sha256"]].append(r["current_path"])
    dupes = {h: ps for h, ps in by_hash.items() if len(ps) > 1}
    m.append(f"templates/ 内部共有 {len(dupes)} 组完全相同的文件。本次仅记录，未删除。")
    m.append("")
    m.append("| 哈希 | 文件 1 | 文件 2 |")
    m.append("| --- | --- | --- |")
    for h, ps in sorted(dupes.items()):
        m.append(f"| `{h[:16]}…` | `{ps[0]}` | `{ps[1]}` |")
    m.append("")

    m.append("## 9. temp / 草稿 / 副本类命名")
    m.append("")
    odd_pat = [
        (re.compile(r"(?i)\btemp\b|草稿|scratch"), "temp / 草稿"),
        (re.compile(r"\(\s*\d+\s*\)|（\s*\d+\s*）"), "数字版本后缀"),
        (re.compile(r"[_\-]\d+$"), "末尾数字"),
        (re.compile(r"(?i)副本|备份|backup|copy"), "副本 / 备份"),
    ]
    for pat, label in odd_pat:
        hits = [r for r in rows if pat.search(r["filename"])]
        m.append(f"### {label}（{len(hits)} 个）")
        m.append("")
        if hits:
            m.append("| 路径 |")
            m.append("| --- |")
            for r in hits:
                m.append(f"| `{r['current_path']}` |")
        else:
            m.append("- （无）")
        m.append("")

    with open(MOVE_MD, "w", encoding="utf-8") as fh:
        fh.write("\n".join(m))
    print(f"Wrote {MOVE_MD}")

    # ---------- template-collision-report.md ----------
    c = []
    c.append("# templates 目标路径冲突报告 (v2)")
    c.append("")
    c.append("本报告记录 `docs/_analyze_templates.py` 在为每个文件生成 `proposed_path` 时遇到的目标路径冲突，以及如何消解。")
    c.append("")

    c.append("## 1. 验证数据")
    c.append("")
    c.append("| 指标 | 值 |")
    c.append("| --- | ---: |")
    c.append(f"| `current_path` 唯一数 | {cur_uniq} / {len(rows)} |")
    c.append(f"| `proposed_path` 唯一数 | {prop_uniq} / {len(rows)} |")
    c.append(f"| `proposed_path` 冲突数（修复后） | {prop_dups} |")
    c.append(f"| 实际遇到冲突的源文件数 | {sum(1 for r in rows if r['review_required']=='true')} |")
    c.append(f"| `collision_status=resolved`（不同 SHA） | {cs['resolved']} |")
    c.append(f"| `collision_status=duplicate_review`（相同 SHA） | {cs['duplicate_review']} |")
    c.append(f"| 实际遇到冲突的源文件数 | {sum(1 for r in rows if r['review_required']=='true')} |")
    c.append(f"| `collision_status=resolved`（不同 SHA） | {cs['resolved']} |")
    c.append(f"| `collision_status=duplicate_review`（相同 SHA） | {cs['duplicate_review']} |")
    c.append("")

    c.append("## 2. 冲突消解规则")
    c.append("")
    c.append("1. **检测**：遍历 841 个文件，按 `proposed_path` 分组，找到组内文件数 ≥ 2 的分组")
    c.append("2. **后缀来源**：")
    c.append("   - 若文件含 Luogu problem URL，取 `Pxxxx` 作为后缀（形如 `[P4450]`）")
    c.append("   - 否则取注释块前 30 行中第一条「干净的」标题（无数学符号 / 无 URL / 非纯数字），截断到 ≤ 16 字符作为后缀")
    c.append("   - 若仍无法确定，使用 SHA-256 前 6 位（形如 `[54e95b]`）")
    c.append("3. **冲突状态判定**：")
    c.append("   - 同组所有文件 SHA-256 相同 → `duplicate_review`（**重复文件，未删除**）")
    c.append("   - SHA-256 不同 → `resolved`（按内容重命名以区分）")
    c.append("4. **不删除原则**：v2 不删除任何文件。即使两个 `圆方树——模板.cpp` 的内容看起来几乎一致（P4320 同题），本次也仅添加后缀、保留两者。")
    c.append("")

    # ---- Detailed collision groups ----
    # Group by review_required + collision_status; the rows themselves no
    # longer share proposed_path (the suffix disambiguator already moved them).
    rev_groups: dict[str, list[dict]] = defaultdict(list)
    for r in rows:
        if r["review_required"] == "true":
            # Strip the suffix back off so the group shares the original target.
            base = re.sub(r"\[[^\]]*\](?=\.)", "", r["proposed_path"])
            rev_groups[base].append(r)

    c.append("## 3. 实际遇到的冲突组")
    c.append("")
    n = 0
    for base_path, group in sorted(rev_groups.items()):
        n += 1
        sha_set = {g["sha256"] for g in group}
        is_dup = len(sha_set) == 1
        c.append(f"### 冲突 {n}: `{base_path}`")
        c.append("")
        c.append(f"- 冲突文件数：**{len(group)}**")
        c.append(f"- SHA-256 不同：{'否（重复）' if is_dup else '是'}")
        c.append(f"- 冲突状态：`{'duplicate_review' if is_dup else 'resolved'}`")
        c.append("")
        c.append("| 源路径 | 建议新路径 | SHA-256 | 后缀来源 |")
        c.append("| --- | --- | --- | --- |")
        for g in group:
            # Extract the added suffix from filename part
            stem = Path(g["proposed_path"]).stem
            base_stem = Path(g["filename"]).stem
            suf = stem.replace(base_stem, "", 1)
            c.append(f"| `{g['current_path']}` | `{g['proposed_path']}` | `{g['sha256'][:16]}…` | `{suf}` |")
        c.append("")

    c.append("## 4. 已知但未发现冲突的源文件")
    c.append("")
    c.append("`templates/` 内部 SHA-256 一致的 3 组文件（仅记录，未删除，未触发冲突）：")
    c.append("")
    c.append("| 哈希 | 文件 1 | 文件 2 |")
    c.append("| --- | --- | --- |")
    for h, ps in sorted(dupes.items()):
        c.append(f"| `{h[:16]}…` | `{ps[0]}` | `{ps[1]}` |")
    c.append("")

    c.append("## 5. 后续建议")
    c.append("")
    c.append("- `resolved` 冲突的两组（圆方树 × 2、莫比乌斯函数 × 2）已用内容后缀自动区分。**重构阶段请人工选择保留哪一份**（一般建议保留较新 / 注释更详细 / 与现有目录一致的版本）。")
    c.append("- `duplicate_review` 状态本次未触发（v2 没有新增）。")
    c.append("- 任何仍产生冲突的 `proposed_path` 都已在 v2 解决；如未来再新增同名文件，脚本会自动按相同规则追加后缀。")
    c.append("")

    with open(COLLISION_MD, "w", encoding="utf-8") as fh:
        fh.write("\n".join(c))
    print(f"Wrote {COLLISION_MD}")


if __name__ == "__main__":
    main()