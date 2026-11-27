# https://www.luogu.com.cn/problem/P1729
# 题意：给定 n，输出自然常数 e 小数点后前 n 位。
# 首行输出 2.，从次行开始每 10 位用空格分组，每 50 位换行。
# 数据范围：n 是需要输出的小数位数，满分数据 n ≤ 10000。
# 算法标签：高精度计算

from mpmath import mp
mp.dps = 10005  
print(mp.e)