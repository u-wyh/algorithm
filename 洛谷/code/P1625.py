# https://www.luogu.com.cn/problem/P1625
# 题意：输入两个整数 n 和 m。
# 计算和式 S = sum_{i=1}^n (1 / prod_{j=i}^{i+m-1} j)。
# 将 S 化为最简分数 X/Y（X, Y 互质），分两行依次输出 X 和 Y。
# 数据范围：
# n > 0，m > 1（整数）
# n + m <= 500
# 算法标签：数学、最大公约数
import math

n, m = map(int, input().split())

sum_num = 0
sum_den = 1

for i in range(1, n + 1):
    denominator = 1
    for j in range(i, i + m):
        denominator *= j
    
    new_num = sum_num * denominator + sum_den
    new_den = sum_den * denominator
    
    common_divisor = math.gcd(new_num, new_den)
    sum_num = new_num // common_divisor
    sum_den = new_den // common_divisor

print(sum_num)
print(sum_den)