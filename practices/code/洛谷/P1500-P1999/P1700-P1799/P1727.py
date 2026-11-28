# https://www.luogu.com.cn/problem/P1727
# 题意：给定 n，输出圆周率小数点后前 n 位。
# 首行输出 3.，从次行开始每 10 位用空格分组，每 50 位换行。
# 数据范围：n 是需要输出的小数位数，满分数据 n ≤ 10000。
# 难度评分：1300（洛谷分级换算）
# 算法标签：Chudnovsky 公式、分治

import sys
from math import isqrt

CUBE_DIV_24 = 640320**3 // 24


def split_terms(left, right):
    if right - left == 1:
        if left == 0:
            return 1, 1, 13591409

        p = (6 * left - 5) * (2 * left - 1) * (6 * left - 1)
        q = left**3 * CUBE_DIV_24
        t = p * (13591409 + 545140134 * left)
        return p, q, -t if left % 2 else t

    mid = (left + right) // 2
    p1, q1, t1 = split_terms(left, mid)
    p2, q2, t2 = split_terms(mid, right)
    return p1 * p2, q1 * q2, t1 * q2 + p1 * t2


def scaled_pi(n):
    extra = 12
    while True:
        precision = n + extra
        terms = precision // 14 + 1
        p, q, t = split_terms(0, terms)
        _, next_q, next_t = split_terms(terms, terms + 1)

        # 相邻交错级数部分和夹住真值，统一分母后取上下界。
        end = t * next_q
        next_end = end + p * next_t
        factor = 426880 * q * next_q
        root = isqrt(10005 * 10 ** (2 * precision))
        divisor = 10**extra
        low = factor * root // (max(end, next_end) * divisor)
        high = factor * (root + 1) // (min(end, next_end) * divisor)
        if low == high:
            return low
        extra += 12


def main():
    n = int(sys.stdin.readline())
    if hasattr(sys, "set_int_max_str_digits"):
        sys.set_int_max_str_digits(0)
    digits = str(scaled_pi(n))[1:]
    print("3.")
    for i in range(0, n, 50):
        line = digits[i:i + 50]
        print(" ".join(line[j:j + 10] for j in range(0, len(line), 10)))


if __name__ == "__main__":
    main()