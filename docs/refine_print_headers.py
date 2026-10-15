"""把打印副本的开头注释改为具体问题；只保留确有必要的注意。"""

from pathlib import Path
from rename_print_templates import NAME_MAP

ROOT = Path(r"D:\algorithm\可打印算法模板")
GENERIC = "// 注意：按具体题目核对输入输出与数组上限。"

# 文件名 -> 代码实际解决的问题。原文件和正文注释不改。
PURPOSE = {
    "01bfs——模板.cpp": "在含 0/1 代价的网格中，求起点到终点最少清除多少障碍",
    "floyd算法——模板.cpp": "用 Floyd 预处理全源最短路，计算指定访问顺序的最短总路程",
    "twosat——模板.cpp": "判断每组二选一约束能否同时满足",
    "边分治——模板.cpp": "在点权树中求所有非空路径的‘路径长度×路径最小点权’最大值",
    "点分树——模板.cpp": "维护树上点权修改，并查询距指定节点不超过 k 的点权和",
    "静态点分治——模板.cpp": "统计树上距离为 3 的倍数的有序点对，并输出其概率",
    "树链剖分——模板.cpp": "维护树上路径和子树的区间加法、区间求和（取模）",
    "树上启发式合并——模板.cpp": "计算每个节点的子树中有多少种不同颜色",
    "虚树——模板.cpp": "对每次给出的关键点，求切断它们两两连通所需删除的最少非关键点数",
    "后缀自动机——模板.cpp": "求每种子串长度乘出现次数的最大值",
    "回文自动机——模板.cpp": "逐位置求以该位置结尾的回文子串个数",
    "失配树——1based模板.cpp": "查询两个前缀的最长公共真前后缀",
    "带权并查集——模板.cpp": "用前缀和差值约束回答区间和，未确定时输出 UNKNOWN",
    "动态KD树——替罪羊树模板.cpp": "动态插入带权平面点并查询矩形内点权和",
    "可持久化并查集——模板.cpp": "保留每次合并后的版本，查询或回退到历史版本的连通关系",
    "树套树——树状数组套线段树.cpp": "维护动态数组的区间排名、第 k 小、前驱和后继",
    "线段树——吉如一线段树.cpp": "维护区间取 min，并查询区间最大值与区间和",
    "线段树合并——模板.cpp": "合并各节点的值域线段树，统计子树内比本节点值大的点数",
    "线段树分裂——模板.cpp": "维护多个可合并、可按值域分裂的权值集合及区间和、第 k 小",
    "01分数规划——模板.cpp": "在 n 对数中删去 k 对，使剩余数的 Σx/Σy 最大",
    "博弈论——sg函数.cpp": "计算分糖豆博弈的 SG 值，统计能使对手必败的首步",
    "杜教筛——模板.cpp": "快速求欧拉函数与莫比乌斯函数的前缀和",
    "高精度——模板.cpp": "计算超出内置整数范围的非负整数加、减、乘、除",
    "扩展欧拉定理——模板.cpp": "指数以十进制大整数给出时，计算 a^b mod m",
    "莫比乌斯反演——倍数关系.cpp": "用莫比乌斯反演计数区间内 gcd 恰为 K 的 N 元组",
    "线性基——向量模板4.cpp": "求无向带权图从 1 到 n 的路径异或和最大值",
    "轮廓线dp——模板.cpp": "统计网格中可种格子的选取方案，要求相邻格不能同时选",
    "数位dp——windy数.cpp": "统计区间内相邻十进制位差至少为 2 的正整数",
    "状压dp——模板.cpp": "判断先后从 1..n 取不同数字、累计到目标值的游戏中先手能否获胜",
    "反悔贪心——模板.cpp": "平衡各位置供需，允许购买、丢弃和按距离搬运，求最小总费用",
    "搜索——双向广搜模板.cpp": "折半枚举两组子集和，计数总重量不超过上限的选取方案",
    "根号分治——模板.cpp": "维护单点修改，并查询下标模 x 等于 y 的元素和",
    "树上莫队——模板.cpp": "离线求树上两点路径中不同数值的个数",
    "线段树分治——模板.cpp": "离线处理边的添加、删除和两点是否连通的查询",
    "只增回滚莫队——模板.cpp": "离线查询区间内‘数值×出现次数’的最大值",
    "带修莫队——模板.cpp": "离线处理单点修改及区间不同数值个数查询",
    "扫描线——区间长度.cpp": "对每个查询点 x，找满足 l≤x≤r 的最短闭区间长度 r-l+1",
    "树状数组——二维数组.cpp": "二维网格单点赋值，并求子矩形元素之和",
    "生成树——最小生成树k算法.cpp": "用 Kruskal 求无向带权图的最小生成树权值",
    "线段树优化建图——模板.cpp": "高效加入点到区间、区间到点的有向边，并求单源最短路",
    "差分约束——模板形式一.cpp": "判断一组变量差值不等式是否有解",
    "LCT——边权模板.cpp": "离线处理图的删边与两点间最小生成树路径最大边权查询",
    "逆元——模板.cpp": "预处理模素数下的整数逆元、阶乘及阶乘逆元",
}

NOTES = {
    "回文自动机——模板.cpp": "本例先用上一个答案解码当前字符，再插入自动机",
    "搜索——双向广搜模板.cpp": "n≤40、重量非负；总和及方案数可能超过 32 位，统一用 long long",
    "轮廓线dp——模板.cpp": "网格宽度决定状态数；本实现使用固定数组并按 1e8 取模",
    "状压dp——模板.cpp": "使用第 1..n 位表示可选数字，n 不能超过 20",
    "线段树——吉如一线段树.cpp": "n≤100000，初值与更新值都须 ≥-100000；区间取 min 只在新值高于严格次大值时整段更新",
    "只增回滚莫队——模板.cpp": "当前答案只增不减；缩回左端后须恢复备份答案",
    "扫描线——区间长度.cpp": "n、m 均不超过 200000；区间和查询坐标可为任意 int 值",
    "反悔贪心——模板.cpp": "购买、丢弃和搬运费用须为非负数",
    "逆元——模板.cpp": "模数须为素数且 1≤n<mod、n≤300000；main 只演示预处理，不输出答案",
}

PURPOSE = {NAME_MAP.get(name, name): purpose for name, purpose in PURPOSE.items()}
NOTES = {NAME_MAP.get(name, name): note for name, note in NOTES.items()}


def main() -> None:
    seen = set()
    removed = 0
    for path in ROOT.rglob("*.cpp"):
        lines = path.read_text(encoding="utf-8").splitlines()
        old = lines[:]
        if GENERIC in lines:
            lines.remove(GENERIC)
            removed += 1
        if path.name in PURPOSE:
            assert lines[0].startswith("// 用途："), path
            lines[0] = f"// 用途：{PURPOSE[path.name]}。"
            seen.add(path.name)
        if path.name == NAME_MAP["01bfs——模板.cpp"]:
            lines[1] = "// 时间：O(行数×列数)。"
        if path.name == NAME_MAP["搜索——双向广搜模板.cpp"]:
            lines[1] = "// 时间：O(n×2^(n/2))，包括排序。"
        if path.name == NAME_MAP["反悔贪心——模板.cpp"]:
            lines[1] = "// 时间：O(S log S)，S 为处理的单位数。"
            lines[2] = "// 空间：O(S)。"
        if path.name in NOTES:
            note = f"// 注意：{NOTES[path.name]}。"
            idx = next((i for i, line in enumerate(lines[:6]) if line.startswith("// 注意：")), None)
            if idx is None:
                lines.insert(3, note)
            else:
                lines[idx] = note
        if lines != old:
            path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    assert seen == PURPOSE.keys(), PURPOSE.keys() - seen
    print(f"用途已核对 {len(seen)} 份；删除通用注意 {removed} 处")


if __name__ == "__main__":
    main()
