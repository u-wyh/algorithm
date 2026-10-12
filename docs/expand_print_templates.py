"""按算法覆盖清单扩充可打印 C++ 模板；保留已有的核验版。"""

from pathlib import Path
import csv
import re
from rename_print_templates import new_path

ROOT = Path(r"D:\algorithm")
REPO = ROOT / "templates"
EXTERNAL = Path(r"C:\Users\wyh15\Documents\code\C++\打印的模板")
TARGET = ROOT / "可打印算法模板"
RENAME = ROOT / "docs" / "原模板文件名对照.tsv"
PROVENANCE = ROOT / "docs" / "扩充模板来源.tsv"

# 来源路径 | 时间复杂度 | 空间复杂度 | 可复用的算法用途。
# @ 开头的路径来自旧打印目录；其余来自 templates 目录。
SPEC = r"""
01_图论/kruskal重构树/P2245.cpp|O(m log m + (n+q) log n)|O(n log n)|Kruskal 重构树处理图上两点的瓶颈值查询
01_图论/tarjan/P1656.cpp|O(n+m)|O(n+m)|Tarjan 求无向图的桥
01_图论/tarjan/点双/P8435.cpp|O(n+m)|O(n+m)|Tarjan 求无向图的点双连通分量
01_图论/tarjan/边双/P8436.cpp|O(n+m)|O(n+m)|Tarjan 求无向图的边双连通分量
01_图论/twosat/HDU3062.cpp|O(n+m)|O(n+m)|强连通分量判断 2-SAT 是否有解
01_图论/图论/P2731.cpp|O(n+m)|O(n+m)|求无向图欧拉路径
01_图论/图论/P7771.cpp|O(n+m)|O(n+m)|求有向图欧拉路径
01_图论/图论/P2910.cpp|O(n³)|O(n²)|Floyd 求多源最短路
01_图论/图论/P4568.cpp|O((n+m)k log(nk))|O((n+m)k)|分层图 Dijkstra 处理有限次特殊边
01_图论/图论/P5905.cpp|最坏 O(n²m + n(m+n)log n)|O(n²+m)|Johnson 求稀疏图全源最短路
01_图论/图论/P5960.cpp|最坏 O(nm)|O(n+m)|差分约束系统的可行性判断
01_图论/网络流/P3381.cpp|O(Fm log n)，F 为增广次数|O(n+m)|最小费用最大流
02_树上问题/树上问题/P3366_2.cpp|O(m log m)|O(n+m)|Kruskal 求无向图最小生成树
01_图论/图论/01bfs——模板.cpp|O(行数×列数)|O(行数×列数)|在含 0/1 代价的网格中求最少清除障碍数
01_图论/图论/拓扑排序——入度删除法.cpp|O(n+m)|O(n+m)|拓扑排序与有向无环图判定
02_树上问题/树上启发式合并/U41492.cpp|O(n log n)|O(n+m)|树上启发式合并统计子树信息
02_树上问题/树上问题/P6086_2.cpp|O(n)|O(n)|线性构造或还原 Prüfer 序列
02_树上问题/树链剖分/P3384.cpp|O(n+q log² n)|O(n)|树链剖分维护路径与子树区间
02_树上问题/树链剖分/P5903.cpp|预处理 O(n log n)，查询 O(1)|O(n log n)|长链剖分快速查询 k 级祖先
02_树上问题/点分治/P2634.cpp|O(n log n)|O(n)|静态点分治统计树上路径
02_树上问题/点分治/P6329.cpp|O((n+q)log² n)|O(n log n)|点分树支持树上动态修改与距离查询
02_树上问题/虚树/CF613D.cpp|预处理 O(n log n)，单次 O(k log n)|O(n log n)|虚树压缩少量关键点的树上询问
03_字符串/AC自动机/P5357.cpp|O(字符总数×字符集大小)|O(节点数×字符集大小)|AC 自动机同时匹配多个模式串
03_字符串/Manacher/P5496.cpp|O(n×字符集大小)|O(n×字符集大小)|回文自动机维护不同回文子串
03_字符串/后缀数组 后缀自动机/P3804.cpp|O(n×字符集大小)|O(n×字符集大小)|后缀自动机处理子串出现次数等问题
03_字符串/后缀数组 后缀自动机/P3809.cpp|O(n log n)|O(n)|后缀数组求字典序与后缀排名
03_字符串/KMP/P5829.cpp|O(n+q log n)|O(n log n)|失配树处理前后缀关系询问
03_字符串/哈希/哈希——算法模板.cpp|O(n+L)，n 为文本长、L 为单词总长|O(n+L)|查找由给定等长单词各用一次、连续拼接而成的所有子串起点
04_数据结构/并查集/P3402.cpp|O((n+q)log n)|O((n+q)log n)|可持久化并查集支持历史版本查询
04_数据结构/并查集/P8779.cpp|O((n+q)α(n))|O(n)|带权并查集维护相对关系
04_数据结构/线段树/P3919.cpp|O((n+q)log n)|O((n+q)log n)|可持久化线段树支持历史版本单点修改
04_数据结构/线段树/P3834.cpp|O((n+q)log V)|O(n log V)|主席树查询静态区间第 k 小
04_数据结构/线段树合并与分裂/P3605.cpp|O(n log V)|O(n log V)|动态线段树合并维护子树值域
04_数据结构/线段树合并与分裂/P5494.cpp|单次 O(log V)|O(节点数)|动态线段树分裂与合并
04_数据结构/树状数组/树状数组——二维数组.cpp|单次 O(log n log m)|O(nm)|二维树状数组支持点改与矩形求和
04_数据结构/线段树/线段树——吉如一线段树.cpp|均摊 O(q log² n)|O(n)|线段树 Beats 处理区间取最值等操作
04_数据结构/杂项数据结构/位图——模板.cpp|单次 O(1)|O(U/字长)|位图压缩布尔值域并快速查询
05_数学数论/数学/P3389.cpp|O(n³)|O(n²)|高斯消元求实数线性方程组
05_数学数论/数学/P2962.cpp|O(n³+n·2^f)，f 为自由元数|O(n²)|异或高斯消元求 GF(2) 方程组
05_数学数论/数学/P4151.cpp|O(nB)|O(B)|线性基求最大异或值
05_数学数论/数学/P3807.cpp|O(p+logₚ n)|O(p)|Lucas 定理求大组合数模质数
05_数学数论/数学/P5367.cpp|O(n log n)|O(n)|康托展开求排列的字典序排名
05_数学数论/数论/P3803_3.cpp|O(n log n)|O(n)|NTT 精确求模意义下多项式卷积
05_数学数论/数论/P4213.cpp|依预处理阈值，约 O(n^(2/3))|约 O(n^(2/3))|杜教筛求积性函数前缀和
05_数学数论/数学/高精度——模板.cpp|乘法 O(L²)|O(L)|高精度整数运算
05_数学数论/数学/逆元——模板.cpp|O(log mod)|O(1)|模意义下求乘法逆元
05_数学数论/01分数规划/01分数规划——模板.cpp|O(log 精度 × 判定代价)|取决于判定算法|01 分数规划的二分答案框架
06_动态规划/动态规划/P1879_2.cpp|O(nm2^m)|O(nm2^m)|递归轮廓线 DP 统计网格合法方案
06_动态规划/动态规划/多重背包——单调队列优化.cpp|O(nW)|O(W)|单调队列优化多重背包
06_动态规划/动态规划/数位dp——windy数.cpp|O(位数×状态数×10)|O(位数×状态数)|记忆化数位 DP 统计满足限制的整数
06_动态规划/动态规划/状压dp——模板.cpp|O(n2^n)|O(2^n)|递归状态压缩 DP 枚举集合决策
07_搜索与贪心/搜索/P4799.cpp|O(n×2^(n/2))，包括排序|O(2^(n/2))|折半枚举子集和并计数不超过上限的方案
07_搜索与贪心/贪心算法/P2748.cpp|O(S log S)，S 为处理的单位数|O(S)|购买、丢弃、搬运的最小总费用
08_离线分治/CDQ分治/P3810.cpp|O(n log² n)|O(n)|CDQ 分治求三维偏序计数
08_离线分治/整体二分/P3834.cpp|O((n+q)log V log n)|O(n+q)|整体二分求离线区间第 k 小
08_离线分治/线段树分治/LOJ121.cpp|O((n+q)log q log n)|O((n+q)log q)|时间线段树分治维护动态约束
08_离线分治/分块 莫队/莫队/P1903.cpp|约 O((n+q)n^(2/3))|O(n+q+V)|带修改莫队处理区间离线查询
08_离线分治/分块 莫队/莫队/SPOJ_COT2.cpp|约 O((n+q)√n)|O(n+q+V)|树上莫队处理路径统计
08_离线分治/分块 莫队/分块/P3396.cpp|O((n+q)√n)|O(n+√n×V)|根号分治处理按步长分类的询问
08_离线分治/分块 莫队/莫队/AT_JOISC2014C.cpp|约 O((n+q)√n)|O(n+q+V)|回滚莫队处理不可逆区间统计
09_基础技巧/二分/P2619.cpp|O(m log m log W)|O(n+m)|带权二分处理恰好选 k 条特殊边
09_基础技巧/差分前缀和/P3397.cpp|O(nm+q)|O(nm)|二维差分处理矩形区间加值
09_基础技巧/差分前缀和/前缀和——二维前缀和.cpp|O(nm+q)|O(nm)|二维前缀和处理静态矩形求和
09_基础技巧/扫描线/扫描线——区间长度.cpp|O((n+m) log(n+m))|O(n+m)|查询每个点所落入的最短闭区间长度
07_搜索与贪心/单调队列单调栈/单调栈——模板.cpp|O(n)|O(n)|单调栈求每个元素两侧第一个严格更小的位置
02_树上问题/边分治/BZOJ2870.cpp|O(n log² n)|O(n log n)|边分治把树上路径统计分为两个连通块
04_数据结构/树套树/P3380.cpp|单次 O(log² n)|O((n+q)log n)|树状数组套线段树维护动态区间排名
05_数学数论/博弈论/P3185.cpp|O(n³)|O(n)|SG 函数求公平组合游戏的必胜策略
模板/仙人掌树/P5236.cpp|预处理 O(n+m)，单次 O(log n)|O(n+m)|圆方树求带权仙人掌图的两点最短路
模板/基环树/CF711D.cpp|O(n)|O(n)|拆出基环树各连通块与环信息
01_图论/图论/CF786B.cpp|O((n+q)log(n+q)log n)|O((n+q)log n)|线段树优化区间连边并求最短路
@KD树/动态KD树——替罪羊树模板.cpp|建树 O(n log n)，查询最坏 O(n)|O(n)|动态 KD 树支持平面点集更新与空间查询
@KD树/KD树——平面最近点对.cpp|建树 O(n log n)，查询最坏 O(n²)|O(n)|KD 树处理平面最近点对
@LCT/LCT——边权模板.cpp|单次均摊 O(log n)|O(n)|LCT 维护动态森林边权路径信息
@平衡树/FHQ treap——可持久化平衡树.cpp|单次期望 O(log n)|O(q log n)|可持久化 FHQ Treap 保留历史版本
@平衡树/FHQ treap——区间翻转.cpp|单次期望 O(log n)|O(n)|隐式 FHQ Treap 支持序列区间翻转
@欧拉函数/扩展欧拉定理——模板.cpp|O(log mod)|O(log mod)|扩展欧拉定理处理大指数取模
@莫比乌斯/莫比乌斯反演——倍数关系.cpp|O(10^5+D log N)，D=⌊H/K⌋-⌈L/K⌉|O(10^5)|用莫比乌斯反演计数区间内 gcd 恰为 K 的 N 元组
"""


def source_text(path: Path) -> str:
    raw = path.read_bytes()
    try:
        text = raw.decode("utf-8")
    except UnicodeDecodeError:
        text = raw.decode("gb18030")
    return text.replace("\r\n", "\n").replace("\r", "\n")


def stripped_body(text: str) -> str:
    lines = text.splitlines(keepends=True)
    i = 0
    while i < len(lines) and (not lines[i].strip() or lines[i].lstrip().startswith("//")):
        i += 1
    return "".join(lines[i:]).lstrip("\n")


def main() -> None:
    old_names = {}
    with RENAME.open(encoding="utf-8", newline="") as file:
        for row in csv.DictReader(file, delimiter="\t"):
            old_names[row["当前文件"].removeprefix("templates/")] = Path(row["改名前文件"]).name
    rows = []
    for entry in SPEC.strip().splitlines():
        rel, time, space, purpose = entry.split("|", 3)
        source_root = EXTERNAL if rel.startswith("@") else REPO
        rel = rel.removeprefix("@")
        source = source_root / rel
        if not source.is_file() or source.stat().st_size == 0:
            raise RuntimeError(f"源文件缺失或为空：{source}")
        category = rel.split("/", 1)[0]
        if category == "模板":
            category = "02_树上问题" if rel.startswith("模板/基环树/") else "01_图论"
        if source_root == EXTERNAL:
            category = {
                "KD树": "04_数据结构", "LCT": "02_树上问题",
                "平衡树": "04_数据结构", "欧拉函数": "05_数学数论",
                "生成函数": "05_数学数论", "莫比乌斯": "05_数学数论",
            }[category]
        name = old_names.get(rel, source.name)
        dest = new_path(TARGET / category / name)
        full = source_text(source)
        links = re.findall(r"https?://[^\s\*]+", full[:3000])
        link = links[0].rstrip("，。);") if links else ""
        header = [
            f"// 用途：{purpose}。",
            f"// 时间：{time}。",
            f"// 空间：{space}。",
        ]
        if link:
            header.append(f"// 例题：{link}")
        prepared = "\n".join(header) + "\n" + stripped_body(full)
        if dest.exists():
            pass  # 已审过的副本可能有修复，不覆盖。
        else:
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_text(prepared, encoding="utf-8")
        rows.append((str(dest), str(source), name, time, space))
    with PROVENANCE.open("w", encoding="utf-8", newline="") as file:
        writer = csv.writer(file, delimiter="\t")
        writer.writerow(["新文件", "源文件", "原文件名", "时间复杂度", "空间复杂度"])
        writer.writerows(rows)
    from refine_print_headers import main as refine_headers
    refine_headers()
    from add_example_explanations import main as add_example_explanations
    add_example_explanations()
    print(f"added={len(rows)} total_cpp={len(list(TARGET.rglob('*.cpp')))}")


if __name__ == "__main__":
    main()
