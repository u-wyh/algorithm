#!/usr/bin/env python3
# templates/ analyzer v2.
#   - Priority: filename's PRIMARY token (the part before "——") defines the
#     main algorithm family.  Anything after "——" is treated as a variant /
#     application / auxiliary technique and does NOT change the main family.
#   - Three-level paths allowed (e.g. templates/图论/网络流/最大流/...).
#   - Collision detection: if two different files produce the same proposed
#     path, find a content-based disambiguator (URL problem ID, first
#     non-trivial comment line, or short hash) and append it as a suffix in
#     the filename.  Same SHA-256 + same name -> mark duplicate_review.
#   - Read-only: never modifies source files.
import csv
import hashlib
import os
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TPL = ROOT / "templates"
DOCS = ROOT / "docs"
CSV_OUT = DOCS / "template-classification-v2.csv"

SOURCE_EXTS = {".cpp", ".cc", ".cxx", ".c", ".h", ".hpp", ".hh", ".hxx", ".inl"}
MAIN_RES = [
    re.compile(r"\bint\s+main\s*\("),
    re.compile(r"\bvoid\s+main\s*\("),
    re.compile(r"\bint\s+MAIN\s*\("),
]
URL_RE = re.compile(r"https?://[^\s\)\]\"'>]+", re.IGNORECASE)
LUOGU_PROBLEM_URL_RE = re.compile(r"luogu\.com\.cn/(?:problem|record)/([A-Za-z0-9_\-]+)", re.IGNORECASE)

# Primary token (the part BEFORE "——") -> (top_category, sub_path).
# Sub-path may itself contain "/" to form three levels (e.g. "网络流/最大流").
# If primary not in the map, the script falls back to secondary-token map,
# then to current directory map, then to "其他".
PRIMARY_MAP: dict[str, tuple[str, str]] = {
    # ===== 数学/数论 =====
    "质数": ("数学", "数论/质数"),
    "素数": ("数学", "数论/质数"),
    "Miller": ("数学", "数论/质数/Miller-Rabin"),
    "Pollard": ("数学", "数论/质数/Pollard-Rho"),
    "快速幂": ("数学", "数论/快速幂"),
    "扩展欧几里得": ("数学", "数论/扩展欧几里得"),
    "扩展欧拉定理": ("数学", "数论/扩展欧拉定理"),
    "中国剩余定理": ("数学", "数论/中国剩余定理"),
    "逆元": ("数学", "数论/逆元"),
    "乘法逆元": ("数学", "数论/逆元"),
    "欧拉函数": ("数学", "数论/欧拉函数"),
    "裴蜀定理": ("数学", "数论/裴蜀定理"),
    "原根": ("数学", "数论/原根"),
    "卢卡斯定理": ("数学", "数论/Lucas"),
    "BSGS": ("数学", "数论/BSGS"),
    "杜教筛": ("数学", "数论/杜教筛"),
    "莫比乌斯函数": ("数学", "数论/莫比乌斯反演"),
    "莫比乌斯反演": ("数学", "数论/莫比乌斯反演"),
    # ===== 数学/组合数学 =====
    "卡特兰数": ("数学", "组合数学/卡特兰数"),
    "二项式反演": ("数学", "组合数学/二项式反演"),
    "二项式定理": ("数学", "组合数学/二项式定理"),
    "康拓展开": ("数学", "组合数学/康拓展开"),
    "组合数": ("数学", "组合数学/组合数"),
    "排列组合": ("数学", "组合数学/排列组合"),
    "约瑟夫环": ("数学", "组合数学/约瑟夫环"),
    "约瑟夫环加强": ("数学", "组合数学/约瑟夫环"),
    # ===== 数学/多项式 =====
    "FFT": ("数学", "多项式/FFT"),
    "NTT": ("数学", "多项式/NTT"),
    # ===== 数学/线性代数 =====
    "矩阵乘法": ("数学", "线性代数/矩阵乘法"),
    "高斯消元": ("数学", "线性代数/高斯消元"),
    "线性基": ("数学", "线性代数/线性基"),
    # ===== 数学/其他数学专题 =====
    "01分数规划": ("数学", "01分数规划"),
    "博弈论": ("数学", "博弈论"),
    "博弈": ("数学", "博弈论"),
    "数论": ("数学", "数论/其他"),
    # ===== 图论/最短路 =====
    "DJ算法": ("图论", "最短路/Dijkstra"),
    "01bfs": ("图论", "最短路/0-1 BFS"),
    "floyd算法": ("图论", "最短路/Floyd"),
    "Floyd": ("图论", "最短路/Floyd"),
    "johnson": ("图论", "最短路/Johnson"),
    "Johnson": ("图论", "最短路/Johnson"),
    "最短路": ("图论", "最短路/通用"),
    "分层最短路": ("图论", "最短路/分层最短路"),
    "同余最短路": ("图论", "最短路/同余最短路"),
    "次短路": ("图论", "最短路/次短路"),
    "k短路": ("图论", "最短路/K短路"),
    "dijkstra": ("图论", "最短路/Dijkstra"),
    "拓扑排序": ("图论", "拓扑排序"),
    # ===== 图论/网络流 =====
    "网络流": ("图论", "网络流/通用"),
    "最大流": ("图论", "网络流/最大流"),
    "最小割": ("图论", "网络流/最小割"),
    "最小费用最大流": ("图论", "网络流/最小费用最大流"),
    "费用流": ("图论", "网络流/最小费用最大流"),
    "上下界网络流": ("图论", "网络流/上下界网络流"),
    # ===== 图论/Tarjan =====
    "tarjan": ("图论", "Tarjan/通用"),
    "Tarjan": ("图论", "Tarjan/通用"),
    "强连通分量": ("图论", "Tarjan/强连通分量"),
    "强连通": ("图论", "Tarjan/强连通分量"),
    "割点": ("图论", "Tarjan/割点"),
    "割边": ("图论", "Tarjan/割边"),
    "桥": ("图论", "Tarjan/割边"),
    "边双": ("图论", "Tarjan/边双连通分量"),
    "边双连通分量": ("图论", "Tarjan/边双连通分量"),
    "点双": ("图论", "Tarjan/点双连通分量"),
    "点双连通分量": ("图论", "Tarjan/点双连通分量"),
    "圆方树": ("图论", "Tarjan/圆方树"),
    # ===== 图论/欧拉路径 =====
    "欧拉回路": ("图论", "欧拉路径"),
    "欧拉路径": ("图论", "欧拉路径"),
    "欧拉图": ("图论", "欧拉路径"),
    # ===== 图论/二分图 =====
    "二分图": ("图论", "二分图/通用"),
    "匈牙利算法": ("图论", "二分图/匈牙利算法"),
    "KM算法": ("图论", "二分图/KM算法"),
    "HK算法": ("图论", "二分图/HK算法"),
    # ===== 图论/生成树 =====
    "生成树": ("图论", "生成树/通用"),
    "最小生成树": ("图论", "生成树/最小生成树"),
    "kruskal重构树": ("图论", "生成树/kruskal重构树"),
    "kruskal": ("图论", "生成树/Kruskal"),
    "prim算法": ("图论", "生成树/Prim"),
    "最小树形图": ("图论", "生成树/最小树形图"),
    # ===== 图论/其他图论 =====
    "虚树": ("图论", "虚树"),
    "边分治": ("图论", "边分治"),
    "twosat": ("图论", "2-SAT"),
    "2-sat": ("图论", "2-SAT"),
    "prufer序": ("图论", "prufer"),
    "prufer": ("图论", "prufer"),
    "图论": ("图论", "通用"),
    "图": ("图论", "通用"),
    # ===== 树上算法 =====
    "LCA": ("树上算法", "LCA"),
    "优化LCA": ("树上算法", "LCA"),
    "优化求LCA": ("树上算法", "LCA"),
    "树上倍增": ("树上算法", "LCA"),
    "树链剖分": ("树上算法", "树链剖分"),
    "长链剖分": ("树上算法", "树链剖分"),
    "树上启发式合并": ("树上算法", "启发式合并"),
    "启发式合并": ("树上算法", "启发式合并"),
    "点分治": ("树上算法", "点分树"),
    "点分树": ("树上算法", "点分树"),
    "静态点分治": ("树上算法", "点分树"),
    "树上分块": ("树上算法", "树上分块"),
    "树上莫队": ("树上算法", "树上莫队"),
    "树上换根": ("树上算法", "树上换根"),
    "树上差分": ("树上算法", "树上差分"),
    "树上问题": ("树上算法", "树上问题"),
    "树的直径": ("树上算法", "树的直径"),
    "树上哈希": ("树上算法", "树上哈希"),
    # ===== 字符串 =====
    "AC自动机": ("字符串", "AC自动机"),
    "基于AC自动机实现的文章词频检测": ("字符串", "AC自动机"),
    "KMP算法": ("字符串", "KMP"),
    "KMP": ("字符串", "KMP"),
    "扩展KMP": ("字符串", "扩展KMP"),
    "扩展KMP(Z算法)": ("字符串", "扩展KMP"),
    "Manacher算法": ("字符串", "Manacher"),
    "Manacher": ("字符串", "Manacher"),
    "后缀数组": ("字符串", "后缀数组"),
    "后缀自动机": ("字符串", "后缀自动机"),
    "前缀树": ("字符串", "前缀树"),
    "可持久化前缀树": ("字符串", "前缀树/可持久化前缀树"),
    "回文自动机": ("字符串", "回文自动机"),
    "失配树": ("字符串", "失配树"),
    # ===== 数据结构/线段树 =====
    "线段树": ("数据结构", "线段树/通用"),
    "可持久化线段树": ("数据结构", "线段树/可持久化线段树"),
    "线段树分治": ("数据结构", "线段树/线段树分治"),
    "线段树合并": ("数据结构", "线段树/线段树合并"),
    "线段树分裂": ("数据结构", "线段树/线段树合并"),
    "线段树优化建图": ("数据结构", "线段树/线段树优化建图"),
    # ===== 数据结构/其他 =====
    "树状数组": ("数据结构", "树状数组"),
    "树状数组加离散化加逆序对": ("数据结构", "树状数组"),
    "平衡树": ("数据结构", "平衡树/通用"),
    "splay树": ("数据结构", "平衡树/splay"),
    "FHQ treap": ("数据结构", "平衡树/FHQ treap"),
    "Treap树": ("数据结构", "平衡树/Treap"),
    "AVL树": ("数据结构", "平衡树/AVL"),
    "笛卡尔树": ("数据结构", "笛卡尔树"),
    "左偏树": ("数据结构", "左偏树"),
    "可持久化左偏树": ("数据结构", "左偏树/可持久化左偏树"),
    "可持久化左偏树2": ("数据结构", "左偏树/可持久化左偏树"),
    "树套树": ("数据结构", "树套树"),
    "二叉树": ("数据结构", "二叉树"),
    "ODT树": ("数据结构", "ODT"),
    "CDQ分治": ("数据结构", "CDQ分治"),
    "CDQ": ("数据结构", "CDQ分治"),
    "哈希": ("数据结构", "哈希"),
    "有序表": ("数据结构", "有序表"),
    # ===== 基础算法 =====
    "二分法": ("基础算法", "二分"),
    "二分查找": ("基础算法", "二分"),
    "二分": ("基础算法", "二分"),
    "三分": ("基础算法", "三分"),
    "带权二分": ("基础算法", "二分/带权二分"),
    "贪心算法": ("基础算法", "贪心"),
    "贪心": ("基础算法", "贪心"),
    "反悔贪心": ("基础算法", "贪心/反悔贪心"),
    "单调栈": ("基础算法", "单调栈"),
    "单调队列": ("基础算法", "单调队列"),
    "前缀和": ("基础算法", "前缀和"),
    "差分": ("基础算法", "差分"),
    "差分约束": ("基础算法", "差分约束"),
    "并查集": ("基础算法", "并查集"),
    "可撤销并查集": ("基础算法", "并查集/可撤销并查集"),
    "带权并查集": ("基础算法", "并查集/带权并查集"),
    "可持久化并查集": ("基础算法", "并查集/可持久化并查集"),
    "并查集分块": ("基础算法", "并查集/并查集分块"),
    "分块": ("基础算法", "分块"),
    "普通分块": ("基础算法", "分块"),
    "双层分块": ("基础算法", "分块/双层分块"),
    "整除分块": ("基础算法", "分块/整除分块"),
    "时间分块": ("基础算法", "分块/时间分块"),
    "块状链表": ("基础算法", "分块/块状链表"),
    "根号分治": ("基础算法", "分块/根号分治"),
    "莫队": ("基础算法", "莫队"),
    "带修莫队": ("基础算法", "莫队/带修莫队"),
    "只删回滚莫队": ("基础算法", "莫队/只删回滚莫队"),
    "只增回滚莫队": ("基础算法", "莫队/只增回滚莫队"),
    "莫队二次离线": ("基础算法", "莫队/二次离线莫队"),
    "倍增和st表": ("基础算法", "倍增"),
    "倍增st表": ("基础算法", "倍增"),
    "st表": ("基础算法", "倍增"),
    "扫描线": ("基础算法", "扫描线"),
    "双指针": ("基础算法", "双指针"),
    "位运算的加减乘除": ("基础算法", "位运算"),
    "位运算的神奇操作": ("基础算法", "位运算"),
    "位图": ("基础算法", "位运算/位图"),
    "异或哈希": ("基础算法", "位运算/异或哈希"),
    "异或的神奇操作": ("基础算法", "位运算/异或"),
    "二进位制打印": ("基础算法", "位运算"),
    "高精度": ("基础算法", "高精度"),
    "排序": ("基础算法", "排序"),
    "归并": ("基础算法", "排序/归并"),
    "归并排序": ("基础算法", "排序/归并排序"),
    "递归函数": ("基础算法", "递归"),
    "递归": ("基础算法", "递归"),
    "枚举子集": ("基础算法", "枚举子集"),
    "前缀信息": ("基础算法", "前缀信息"),
    "整体二分": ("基础算法", "整体二分"),
    "随机化": ("基础算法", "随机化"),
    "洪水填充": ("基础算法", "洪水填充"),
    "dfn序": ("基础算法", "dfn序"),
    "dfs": ("基础算法", "DFS"),
    # ===== 动态规划 =====
    "动态规划": ("动态规划", "通用DP"),
    "动态规划优化": ("动态规划", "DP优化"),
    "DP": ("动态规划", "通用DP"),
    "dp": ("动态规划", "通用DP"),
    "状压dp": ("动态规划", "状压DP"),
    "状压DP": ("动态规划", "状压DP"),
    "数位dp": ("动态规划", "数位DP"),
    "数位DP": ("动态规划", "数位DP"),
    "树形dp": ("动态规划", "树形DP"),
    "树形DP": ("动态规划", "树形DP"),
    "区间dp": ("动态规划", "区间DP"),
    "区间DP": ("动态规划", "区间DP"),
    "轮廓线dp": ("动态规划", "轮廓线DP"),
    "轮廓线DP": ("动态规划", "轮廓线DP"),
    "三进制状压dp": ("动态规划", "状压DP"),
    "三进制状压dp2": ("动态规划", "状压DP"),
    "多重背包": ("动态规划", "背包DP"),
    # ===== 搜索 =====
    "搜索": ("搜索", "通用"),
    "DFS": ("搜索", "DFS"),
    "BFS": ("搜索", "BFS"),
    "IDA*": ("搜索", "IDA*"),
    "A*": ("搜索", "A*"),
    "TSP": ("搜索", "TSP"),
    "tsp结合三进制状压": ("搜索", "TSP"),
}

# Map for files whose primary is a *current directory* name (only used when
# primary not in PRIMARY_MAP).  Used as a tie-breaker.
DIR_FALLBACK_MAP = {
    "01分数规划": ("数学", "01分数规划"),
    "AC自动机": ("字符串", "AC自动机"),
    "CDQ分治": ("数据结构", "CDQ分治"),
    "KMP": ("字符串", "KMP"),
    "Manacher": ("字符串", "Manacher"),
    "kruskal重构树": ("图论", "生成树/kruskal重构树"),
    "tarjan": ("图论", "Tarjan/通用"),
    "twosat": ("图论", "2-SAT"),
    "二分图": ("图论", "二分图/通用"),
    "倍增st表": ("基础算法", "倍增"),
    "分块 莫队": ("基础算法", "分块"),
    "前缀树": ("字符串", "前缀树"),
    "动态规划": ("动态规划", "通用DP"),
    "单调队列单调栈": ("基础算法", "单调队列"),
    "博弈论": ("数学", "博弈论"),
    "后缀数组 后缀自动机": ("字符串", "后缀数组"),
    "哈希": ("数据结构", "哈希"),
    "图论": ("图论", "通用"),
    "左偏树": ("数据结构", "左偏树"),
    "差分前缀和": ("基础算法", "前缀和"),
    "平衡树": ("数据结构", "平衡树/通用"),
    "并查集": ("基础算法", "并查集"),
    "扩展KMP": ("字符串", "扩展KMP"),
    "搜索": ("搜索", "通用"),
    "数学": ("数学", "数论/其他"),
    "数论": ("数学", "数论/其他"),
    "整体二分": ("基础算法", "整体二分"),
    "树上启发式合并": ("树上算法", "启发式合并"),
    "树上问题": ("树上算法", "树上问题"),
    "树套树": ("数据结构", "树套树"),
    "树状数组": ("数据结构", "树状数组"),
    "树链剖分": ("树上算法", "树链剖分"),
    "欧拉回路": ("图论", "欧拉路径"),
    "点分治": ("树上算法", "点分树"),
    "线段树": ("数据结构", "线段树/通用"),
    "线段树分治": ("数据结构", "线段树/线段树分治"),
    "线段树合并与分裂": ("数据结构", "线段树/线段树合并"),
    "网络流": ("图论", "网络流/通用"),
    "虚树": ("图论", "虚树"),
    "贪心算法": ("基础算法", "贪心"),
    "边分治": ("图论", "边分治"),
    "优化求LCA": ("树上算法", "LCA"),
}


def split_primary_secondary(filename: str) -> tuple[str, str]:
    """Return (primary, secondary).  Primary is everything before the FIRST
    '——' (or '--' fallback); secondary is the rest, including any further
    '——' segments.  If no separator exists, primary = stem, secondary = ''."""
    for sep in ("——", "--"):
        if sep in filename:
            parts = filename.split(sep, 1)
            return parts[0].strip(), parts[1].strip()
    if " - " in filename:
        parts = filename.split(" - ", 1)
        return parts[0].strip(), parts[1].strip()
    stem = Path(filename).stem
    return stem, ""


def sha256_of(path: Path) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 16), b""):
            h.update(chunk)
    return h.hexdigest()


def line_count(path: Path) -> int:
    with open(path, "rb") as fh:
        return sum(1 for _ in fh)


def read_text(path: Path) -> str:
    try:
        with open(path, "rb") as fh:
            data = fh.read()
    except OSError:
        return ""
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError:
        return data.decode("gbk", errors="ignore")


def first_comment_block(text: str, max_lines: int = 60) -> list[str]:
    lines = text.splitlines()
    block = []
    in_block = False
    for line in lines[:max_lines * 2]:
        s = line.strip()
        if s.startswith("//"):
            block.append(line)
            continue
        if s.startswith("/*"):
            in_block = True
            block.append(line)
            if "*/" in s:
                in_block = False
            continue
        if in_block:
            block.append(line)
            if "*/" in s:
                in_block = False
            continue
        if s == "" and block:
            continue
        break
    return block[:max_lines]


def has_main(text: str) -> bool:
    if "main" not in text:
        return False
    return any(p.search(text) for p in MAIN_RES)


def extract_urls(text: str) -> list[str]:
    seen = set()
    out = []
    for m in URL_RE.finditer(text):
        u = m.group(0).rstrip(".,;:")
        if u not in seen:
            seen.add(u)
            out.append(u)
    return out


def extract_first_luogu_problem_id(text: str) -> str:
    """Pull the first Pxxxx problem identifier from a Luogu problem URL."""
    for u in URL_RE.finditer(text):
        m = LUOGU_PROBLEM_URL_RE.search(u.group(0))
        if m:
            return m.group(1)
    return ""


def detect_file_kind(filename: str, head_lines: list[str], full_text: str, has_main_flag: bool) -> str:
    base = filename.lower()
    full = "\n".join(head_lines) + "\n" + full_text[:200]
    has_input = any(tok in full for tok in ("scanf", "cin >", "cin>>", "read(", "getline"))
    n_head = len(head_lines)
    if not has_main_flag and n_head < 25 and not has_input:
        return "pure_template"
    if not has_main_flag and n_head < 60 and not has_input:
        return "pure_template"
    if any(h in base or h in full for h in ("应用", "实战")):
        return "application"
    if any(h in base or h in full for h in ("例题", "示例", "经典", "展示", "演示")):
        return "example"
    if any(h in base for h in ("模板", "板子")):
        return "runnable_template"
    if has_input:
        return "application"
    if has_main_flag:
        return "runnable_template"
    return "uncertain"


def classify(filename: str, current_dir: str, full_text: str, head_text: str) -> dict:
    primary, secondary = split_primary_secondary(filename)
    # Strip numeric suffix like "(2)" from primary to make map lookup stable
    primary_clean = re.sub(r"\s*[\(（]\d+[\)）]\s*$", "", primary)
    basis = ""

    chosen = PRIMARY_MAP.get(primary_clean)
    if chosen is not None:
        basis = "primary_filename"
    else:
        chosen = DIR_FALLBACK_MAP.get(current_dir)
        if chosen is not None:
            basis = "current_directory"
    if chosen is None:
        # Final fallback: any keyword anywhere in filename (handles edge cases
        # like 边双 inside 边双——并查集, where primary should already match)
        for k, v in PRIMARY_MAP.items():
            if k and k in filename:
                chosen = v
                basis = "keyword_in_filename_fallback"
                break
    if chosen is None:
        chosen = ("其他", "未分类")
        basis = "no_match"

    top_cat, sub_path = chosen
    proposed_path = f"templates/{top_cat}/{sub_path}/{filename}"

    # Determine primary/secondary algorithm fields.
    primary_alg = primary_clean
    secondary_techs = []
    if secondary:
        # split secondary by —— / - / _ for multiple techniques
        for tok in re.split(r"[——\-_、,， ]+", secondary):
            tok = tok.strip()
            if tok and len(tok) >= 2 and tok not in secondary_techs:
                secondary_techs.append(tok)
    return {
        "primary_algorithm": primary_alg,
        "secondary_techniques": ",".join(secondary_techs),
        "proposed_path": proposed_path,
        "proposed_top_category": top_cat,
        "proposed_subcategory": sub_path,
        "classification_basis": basis,
    }


def find_disambiguator(file_path: Path, sha: str, text: str, head: list[str]) -> str:
    """Return a short suffix string to break a filename collision.  Tries:
       1. The first Luogu problem ID (Pxxxx).
       2. The first non-trivial comment line that looks like a clean title
          (no math symbols, no obvious code).
       3. Short hash tag."""
    pid = extract_first_luogu_problem_id(text)
    if pid:
        return f"[{pid}]"
    # Look for first non-trivial comment line that looks like a clean title
    math_symbols = set("μσπ∑∏√∂∫≡≈≤≥≠∞φδεθλΩαβγ")
    for line in head[:30]:
        s = line.strip().lstrip("/").strip()
        if not s:
            continue
        # Skip URLs and obvious code snippets
        if "://" in s:
            continue
        if any(ch in s for ch in math_symbols):
            continue
        if re.match(r"^[\d\s=+\-*/.,()\[\]{}]+$", s):
            continue
        # Take a sanitized 4-24-char slice as title
        s = re.sub(r"[\s,，。；;、]+", "_", s)
        s = re.sub(r"[^\w一-鿿_\-]", "", s)
        if 4 <= len(s) <= 24:
            return f"[{s[:16]}]"
    return f"[{sha[:6]}]"


def main():
    files = []
    for dirpath, dirnames, filenames in os.walk(TPL):
        dirnames[:] = [d for d in dirnames if d not in (".git",)]
        for fn in filenames:
            ext = Path(fn).suffix.lower()
            if ext not in SOURCE_EXTS:
                continue
            files.append(Path(dirpath) / fn)
    files.sort()
    print(f"Scanning {len(files)} source files under {TPL}")

    rows = []
    by_hash: dict[str, list[str]] = defaultdict(list)

    for fp in files:
        rel = fp.relative_to(ROOT)
        rel_posix = str(rel).replace(os.sep, "/")
        size = fp.stat().st_size
        lines = line_count(fp)
        sha = sha256_of(fp)
        by_hash[sha].append(rel_posix)

        text = read_text(fp)
        head = first_comment_block(text, max_lines=60)
        head_text = "\n".join(head)
        urls = extract_urls(text)
        ids = re.findall(r"(?<![\w/])P\d{2,5}[A-Za-z]?(?![\w])", text)
        pid = extract_first_luogu_problem_id(text)
        main_flag = has_main(text)

        parts = rel.parts
        current_category = parts[1] if len(parts) > 2 else "<root>"

        cls = classify(fp.name, current_category, text, head_text)
        kind = detect_file_kind(fp.name, head, text, main_flag)

        rows.append({
            "current_path": rel_posix,
            "filename": fp.name,
            "extension": fp.suffix.lower().lstrip("."),
            "size_bytes": size,
            "lines": lines,
            "sha256": sha,
            "has_main": "true" if main_flag else "false",
            "primary_algorithm": cls["primary_algorithm"],
            "secondary_techniques": cls["secondary_techniques"],
            "current_category": current_category,
            "proposed_top_category": cls["proposed_top_category"],
            "proposed_subcategory": cls["proposed_subcategory"],
            "proposed_path": cls["proposed_path"],
            "file_kind": kind,
            "classification_basis": cls["classification_basis"],
            "collision_status": "none",
            "review_required": "false",
            "actual_problem_url": urls[0] if urls else "",
            "possible_problem_id": pid,
            "url_count": len(urls),
            "problem_id_count": len(set(ids)),
            "first_comment_lines": len(head),
            "confidence": "medium",
            "reason": cls["classification_basis"],
        })

    # ---------------- Collision detection + resolution ----------------
    # Group by proposed_path; for collisions find a disambiguator per file.
    by_prop: dict[str, list[dict]] = defaultdict(list)
    for r in rows:
        by_prop[r["proposed_path"]].append(r)

    collisions_found = []  # one entry per collision group
    for prop_path, group in list(by_prop.items()):
        if len(group) < 2:
            continue
        # Compute disambiguator per file
        suffixes = []
        for r in group:
            rel_parts = r["current_path"].split("/")[1:]
            fp = TPL.joinpath(*rel_parts)
            txt = read_text(fp)
            head = first_comment_block(txt, max_lines=60)
            suf = find_disambiguator(fp, r["sha256"], txt, head)
            suffixes.append(suf)
        # If all suffixes identical, fall back to hash
        if len(set(suffixes)) != len(suffixes):
            suffixes = [f"[{r['sha256'][:6]}]" for r in group]
        sha_set = {g["sha256"] for g in group}
        all_same_sha = len(sha_set) == 1
        old_path = group[0]["proposed_path"]
        for r, suf in zip(group, suffixes):
            p = Path(r["proposed_path"])
            new_name = p.stem + suf + p.suffix
            new_path = str(p.parent / new_name).replace(os.sep, "/")
            r["proposed_path"] = new_path
            if all_same_sha:
                r["collision_status"] = "duplicate_review"
            else:
                r["collision_status"] = "resolved"
            r["review_required"] = "true"
        collisions_found.append({
            "original_path": old_path,
            "files": [g["current_path"] for g in group],
            "suffixes": suffixes,
            "sha_distinct": not all_same_sha,
            "final_paths": [r["proposed_path"] for r in group],
        })

    # ---------------- Confidence assignment ----------------
    # high: filename primary matched AND basis is "primary_filename" AND
    #       no collision status required review.
    # medium: directory fallback OR secondary-only match OR collision review.
    # low: no match (其他) OR review_required.
    for r in rows:
        if r["review_required"] == "true":
            r["confidence"] = "medium" if r["collision_status"] == "resolved" else "low"
        elif r["classification_basis"] == "primary_filename":
            # Cross-check: if current_category is wildly different from
            # proposed top, downgrade to medium (helps catch错位).
            cur_low = r["current_category"].lower()
            prop_top = r["proposed_top_category"]
            related = {
                "01分数规划": {"数学"},
                "图论": {"图论", "数学", "基础算法"},
                "树上算法": {"树上算法", "图论", "基础算法"},
                "数据结构": {"数据结构", "图论", "树上算法", "数学", "字符串", "基础算法", "动态规划"},
                "动态规划": {"动态规划", "基础算法", "数学", "树上算法"},
                "字符串": {"字符串", "数据结构"},
                "数学": {"数学", "基础算法", "动态规划"},
                "基础算法": {"基础算法", "数学", "数据结构", "动态规划"},
                "搜索": {"搜索", "基础算法", "图论"},
            }
            if prop_top == "其他":
                r["confidence"] = "low"
            elif cur_low in related and prop_top not in related.get(cur_low, set()):
                r["confidence"] = "medium"
            else:
                r["confidence"] = "high"
        elif r["classification_basis"] == "current_directory":
            r["confidence"] = "medium"
        elif r["classification_basis"] == "keyword_in_filename_fallback":
            r["confidence"] = "medium"
        else:
            r["confidence"] = "low"

    # ---------------- Write CSV ----------------
    fields = [
        "current_path", "filename", "extension", "size_bytes", "lines", "sha256",
        "has_main", "primary_algorithm", "secondary_techniques",
        "current_category", "proposed_top_category", "proposed_subcategory",
        "proposed_path", "file_kind", "classification_basis",
        "collision_status", "review_required",
        "actual_problem_url", "possible_problem_id",
        "url_count", "problem_id_count", "first_comment_lines",
        "confidence", "reason",
    ]
    with open(CSV_OUT, "w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=fields)
        w.writeheader()
        w.writerows(rows)
    print(f"Wrote {CSV_OUT} with {len(rows)} rows")

    # ---------------- Validation block ----------------
    cur_paths = [r["current_path"] for r in rows]
    prop_paths = [r["proposed_path"] for r in rows]
    cur_uniq = len(set(cur_paths))
    prop_uniq = len(set(prop_paths))
    prop_collisions = len(prop_paths) - prop_uniq
    conf_counter = Counter(r["confidence"] for r in rows)
    review_counter = Counter(r["review_required"] for r in rows)
    cs_counter = Counter(r["collision_status"] for r in rows)
    print()
    print("=== Validation ===")
    print(f"Total rows: {len(rows)}")
    print(f"current_path unique count: {cur_uniq} (duplicates: {len(cur_paths) - cur_uniq})")
    print(f"proposed_path unique count: {prop_uniq} (duplicates: {prop_collisions})")
    print(f"Confidence: high={conf_counter['high']}  medium={conf_counter['medium']}  low={conf_counter['low']}")
    print(f"review_required: true={review_counter['true']}  false={review_counter['false']}")
    print(f"collision_status: none={cs_counter['none']}  resolved={cs_counter['resolved']}  duplicate_review={cs_counter['duplicate_review']}")
    print()
    print("=== Top-level category distribution ===")
    for c, n in Counter(r["proposed_top_category"] for r in rows).most_common():
        print(f"  {c or '<none>':20s}  {n}")
    print()
    print("=== Collision groups ===")
    if not collisions_found:
        print("  (none)")
    else:
        for col in collisions_found:
            print(f"  {col['original_path']}")
            for f, s in zip(col["files"], col["suffixes"]):
                print(f"    {f}  -> suffix {s}")


if __name__ == "__main__":
    main()