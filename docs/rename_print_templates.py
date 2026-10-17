"""按代码功能整理打印模板文件名，并保留旧打印名对照。"""

from pathlib import Path
import csv

ROOT = Path(r"D:\algorithm\可打印算法模板")
MANIFEST = Path(r"D:\algorithm\docs\打印模板文件名对照.tsv")

# 旧打印相对路径 | 新打印相对路径。命名规则：算法名——具体问题或操作.cpp。
PAIRS = r"""
01_图论/01bfs——模板.cpp|01_图论/0-1 BFS——网格最少清障.cpp
01_图论/边双——模板.cpp|01_图论/Tarjan——边双连通分量.cpp
01_图论/差分约束——模板形式一.cpp|01_图论/差分约束——判定可行性.cpp
01_图论/点双——模板.cpp|01_图论/Tarjan——点双连通分量.cpp
01_图论/欧拉图——欧拉路径模板.cpp|01_图论/欧拉路径——有向图.cpp
01_图论/欧拉图——欧拉路径模板（无向图）.cpp|01_图论/欧拉路径——无向图.cpp
01_图论/仙人掌树——圆方树模板.cpp|01_图论/圆方树——仙人掌两点最短路.cpp
01_图论/线段树优化建图——模板.cpp|01_图论/线段树优化建图——区间连边最短路.cpp
01_图论/最小费用最大流——dijkstra.cpp|01_图论/最小费用最大流——Dijkstra增广.cpp
01_图论/DJ算法——分层最短路模板.cpp|01_图论/分层Dijkstra——限次免费边最短路.cpp
01_图论/floyd算法——模板.cpp|01_图论/Floyd——指定路线最短总路程.cpp
01_图论/johnson——模板.cpp|01_图论/Johnson——全源最短路.cpp
01_图论/kruskal重构树——模板.cpp|01_图论/Kruskal重构树——两点瓶颈值.cpp
01_图论/tarjan——桥模板.cpp|01_图论/Tarjan——桥.cpp
01_图论/twosat——模板.cpp|01_图论/2-SAT——可满足性判定.cpp
02_树上问题/边分治——模板.cpp|02_树上问题/边分治——路径长度乘最小点权.cpp
02_树上问题/点分树——模板.cpp|02_树上问题/点分树——点权修改与距离内求和.cpp
02_树上问题/基环树——模板.cpp|02_树上问题/基环树——无环定向方案数.cpp
02_树上问题/静态点分治——模板.cpp|02_树上问题/点分治——距离模3为0的点对概率.cpp
02_树上问题/生成树——最小生成树k算法.cpp|01_图论/Kruskal——最小生成树.cpp
02_树上问题/树链剖分——模板.cpp|02_树上问题/树链剖分——路径与子树加和.cpp
02_树上问题/树上启发式合并——模板.cpp|02_树上问题/树上启发式合并——子树不同颜色数.cpp
02_树上问题/虚树——模板.cpp|02_树上问题/虚树——隔离关键点最少删点.cpp
02_树上问题/长链剖分——模板.cpp|02_树上问题/长链剖分——k级祖先.cpp
02_树上问题/LCT——边权模板.cpp|02_树上问题/LCT——删边后最小生成树瓶颈查询.cpp
02_树上问题/prufer序——线性模板.cpp|02_树上问题/Prufer序——编码与还原.cpp
03_字符串/哈希——算法模板.cpp|03_字符串/字符串哈希与滑动窗口——等长单词拼接.cpp
03_字符串/AC自动机——fail树.cpp|03_字符串/AC自动机Fail树——打印文本中的模式串出现次数.cpp
05_数学数论/随机化——k倍问题.cpp|05_数学数论/随机权重集合哈希——区间频次整除判定.cpp
03_字符串/后缀数组——模板.cpp|03_字符串/后缀数组——后缀排序与排名.cpp
03_字符串/后缀自动机——模板.cpp|03_字符串/后缀自动机——子串出现次数乘长度.cpp
03_字符串/回文自动机——模板.cpp|03_字符串/回文自动机——每位置回文后缀数.cpp
03_字符串/失配树——1based模板.cpp|03_字符串/失配树——两个前缀的公共真前后缀.cpp
03_字符串/AC自动机——模板.cpp|03_字符串/AC自动机——多模式串匹配.cpp
04_数据结构/带权并查集——模板.cpp|04_数据结构/带权并查集——区间和约束查询.cpp
04_数据结构/动态KD树——替罪羊树模板.cpp|04_数据结构/动态KD树——插点与矩形求和.cpp
04_数据结构/可持久化并查集——模板.cpp|04_数据结构/可持久化并查集——历史连通性.cpp
04_数据结构/可持久化线段树——单点修改模板.cpp|04_数据结构/可持久化线段树——历史版本单点修改.cpp
04_数据结构/树套树——树状数组套线段树.cpp|04_数据结构/树套树——动态区间排名与第k小.cpp
04_数据结构/树状数组——二维数组.cpp|04_数据结构/二维树状数组——单点赋值与矩形求和.cpp
04_数据结构/位图——模板.cpp|04_数据结构/位图——布尔值域集合.cpp
04_数据结构/线段树——吉如一线段树.cpp|04_数据结构/线段树Beats——区间取min与求和.cpp
04_数据结构/线段树分裂——模板.cpp|04_数据结构/线段树分裂——权值集合拆分合并.cpp
04_数据结构/线段树合并——模板.cpp|04_数据结构/线段树合并——子树较大值个数.cpp
04_数据结构/FHQ treap——可持久化平衡树.cpp|04_数据结构/可持久化FHQ_Treap——历史版本有序集合.cpp
04_数据结构/FHQ treap——区间翻转.cpp|04_数据结构/隐式FHQ_Treap——区间翻转.cpp
05_数学数论/01分数规划——模板.cpp|05_数学数论/01分数规划——删k项最大化比值.cpp
05_数学数论/博弈论——sg函数.cpp|05_数学数论/SG函数——分糖豆博弈.cpp
05_数学数论/杜教筛——模板.cpp|05_数学数论/杜教筛——欧拉函数与莫比乌斯前缀和.cpp
05_数学数论/高精度——模板.cpp|05_数学数论/高精度——非负整数四则运算.cpp
05_数学数论/高斯消元——加法模板.cpp|05_数学数论/高斯消元——实数方程组.cpp
05_数学数论/高斯消元——异或模板.cpp|05_数学数论/异或高斯消元——GF2方程组.cpp
05_数学数论/康拓展开——模板.cpp|05_数学数论/康托展开——排列排名.cpp
05_数学数论/扩展欧拉定理——模板.cpp|05_数学数论/扩展欧拉定理——大指数模幂.cpp
05_数学数论/卢卡斯定理——模板.cpp|05_数学数论/Lucas定理——求C(n+m,m)模质数.cpp
05_数学数论/莫比乌斯反演——倍数关系.cpp|05_数学数论/莫比乌斯反演——N元组最大公约数.cpp
05_数学数论/逆元——模板.cpp|05_数学数论/逆元——整数与阶乘逆元预处理.cpp
05_数学数论/线性基——向量模板4.cpp|05_数学数论/线性基——图路径最大异或和.cpp
05_数学数论/NTT——模板.cpp|05_数学数论/NTT——多项式卷积.cpp
06_动态规划/轮廓线dp——模板.cpp|06_动态规划/轮廓线DP——网格不相邻选格方案.cpp
06_动态规划/多重背包——单调队列优化.cpp|06_动态规划/多重背包——限量硬币最少张数及选取数量.cpp
06_动态规划/数位dp——windy数.cpp|06_动态规划/数位DP——Windy数计数.cpp
06_动态规划/状压dp——模板.cpp|06_动态规划/状压DP——CanIWin先手必胜.cpp
07_搜索与贪心/单调栈——模板.cpp|07_搜索与贪心/单调栈——两侧首个严格更小位置.cpp
07_搜索与贪心/反悔贪心——模板.cpp|07_搜索与贪心/反悔贪心——供需搬运最小费用.cpp
07_搜索与贪心/搜索——双向广搜模板.cpp|07_搜索与贪心/折半搜索——限重子集计数.cpp
08_离线分治/带修莫队——模板.cpp|08_离线分治/带修莫队——区间不同数计数.cpp
08_离线分治/CDQ分治——四维偏序优化dp.cpp|08_离线分治/CDQ四维偏序——宝藏链最大收益及方案数.cpp
08_离线分治/CDQ分治——四维偏序.cpp|08_离线分治/CDQ四维偏序——含负权怪兽链最大收益.cpp
08_离线分治/CDQ分治——优化dp模板.cpp|08_离线分治/CDQ优化DP——导弹最长拦截与入选概率.cpp
08_离线分治/CDQ分治——优化动态规划.cpp|08_离线分治/CDQ优化DP——任意单点变值仍不下降的最长子序列.cpp
08_离线分治/时间分块——序列.cpp|08_离线分治/时间分块——位置值达到阈值的历史时刻数.cpp
08_离线分治/树上分块——重链序列分块.cpp|08_离线分治/树上分块——多路径点权并集与mex.cpp
08_离线分治/整体二分——带修改.cpp|08_离线分治/整体二分——单点修改区间第k小.cpp
08_离线分治/莫队区间不同数.cpp|08_离线分治/普通莫队——静态区间不同数计数.cpp
08_离线分治/根号分治——模板.cpp|08_离线分治/根号分治——模下标求和与单点修改.cpp
08_离线分治/树上莫队——模板.cpp|08_离线分治/树上莫队——路径不同数计数.cpp
08_离线分治/线段树分治——模板.cpp|08_离线分治/时间线段树分治——动态连通性.cpp
08_离线分治/整体二分——模板1.cpp|08_离线分治/整体二分——区间第k小.cpp
08_离线分治/只增回滚莫队——模板.cpp|08_离线分治/回滚莫队——区间值乘频次最大值.cpp
09_基础技巧/差分——二维模板.cpp|09_基础技巧/二维差分——矩形加值.cpp
09_基础技巧/前缀和——二维前缀和.cpp|09_基础技巧/二维前缀和——静态矩形求和.cpp
09_基础技巧/带权二分——模板.cpp|09_基础技巧/带权二分——恰选k条特殊边最小生成树.cpp
09_基础技巧/扫描线——区间长度.cpp|09_基础技巧/扫描线——查询点的最短覆盖区间.cpp
"""

RENAMES = dict(tuple(line.split("|", 1)) for line in PAIRS.strip().splitlines())
NAME_MAP = {Path(old).name: Path(new).name for old, new in RENAMES.items()}


def new_path(path: Path) -> Path:
    rel = path.relative_to(ROOT).as_posix()
    return ROOT / RENAMES.get(rel, rel)


def main() -> None:
    old_paths = [ROOT / old for old in RENAMES]
    new_paths = [ROOT / new for new in RENAMES.values()]
    assert len(RENAMES) == len(new_paths) == len(set(new_paths))
    assert len(NAME_MAP) == len(RENAMES), "旧文件名跨目录重复，须用相对路径映射"
    for old, new in zip(old_paths, new_paths):
        assert old.is_file() != new.is_file(), (old, new)
        assert old.resolve().is_relative_to(ROOT.resolve())
        assert new.resolve().is_relative_to(ROOT.resolve())
    rows = []
    for old, new in zip(old_paths, new_paths):
        current = old if old.is_file() else new
        purpose = current.read_text(encoding="utf-8").splitlines()[0].removeprefix("// 用途：")
        rows.append((str(old), str(new), purpose))
    for old, new in zip(old_paths, new_paths):
        if old.is_file():
            new.parent.mkdir(parents=True, exist_ok=True)
            old.rename(new)
    with MANIFEST.open("w", encoding="utf-8", newline="") as file:
        writer = csv.writer(file, delimiter="\t")
        writer.writerow(("旧打印文件", "现打印文件", "解决的问题"))
        writer.writerows(rows)
    print(f"renamed={len(rows)} total_cpp={len(list(ROOT.rglob('*.cpp')))}")


if __name__ == "__main__":
    main()
