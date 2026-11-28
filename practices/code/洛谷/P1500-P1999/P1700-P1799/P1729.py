# https://www.luogu.com.cn/problem/P1729
# 题意：给定 n，输出自然常数 e 小数点后前 n 位。
# 首行输出 2.，从次行开始每 10 位用空格分组，每 50 位换行。
# 数据范围：n 是需要输出的小数位数，满分数据 n ≤ 10000。
# 难度评分：1300（洛谷分级换算）
# 算法标签：高精度计算、级数求和

import sys
from itertools import count


def scaled_e(n):
    scale = 10**n
    numerator = denominator = 1
    for k in count(1):
        numerator = numerator * k + 1
        denominator *= k
        if denominator <= scale:
            continue

        # 第 k 项之后的级数余项小于 1/(k·k!)。
        value, remainder = divmod(scale * numerator, denominator)
        if remainder * k + scale <= denominator * k:
            return value


def main():
    n = int(sys.stdin.readline())
    if hasattr(sys, "set_int_max_str_digits"):
        sys.set_int_max_str_digits(0)
    digits = str(scaled_e(n))[1:]
    print("2.")
    for i in range(0, n, 50):
        line = digits[i:i + 50]
        print(" ".join(line[j:j + 10] for j in range(0, len(line), 10)))


if __name__ == "__main__":
    main()