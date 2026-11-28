# https://www.luogu.com.cn/problem/P1487
# 题意：输入整数 n, m 和实数 d, A_1, A_n。
# 已知长为 n 的实数数列
# 满足 A_i = (A_{i-1} - A_{i+1})/2 + d。
# 输出第 m 项 A_m 的值，保留 3 位小数。
# 数据范围：
# 1 <= n <= 60（数列长度）
# 0 <= m <= n（查询下标）
# |d|, |A_1|, |A_n| < 10^4（实数）
# 难度评分：1600（洛谷分级换算）
# 算法标签：递推、数学
import sys

def main():
    data = sys.stdin.read().split()
    n = int(data[0])
    m = int(data[1])
    d = float(data[2])
    a1 = float(data[3])
    an = float(data[4])

    if(m==0):
        print("0.000")
        return 
    
    # 如果a1等于d，直接输出d
    if abs(a1 - d) < 1e-9:
        print(f"{d:.3f}")
        return
    
    # 初始化f数组，大小为n（至少需要索引n-1）
    f = [0] * (n + 1)
    f[0] = 0
    f[1] = 1
    
    # 计算f[2]到f[n-1]
    for i in range(2, n):
        f[i] = 2 * f[i-1] + f[i-2]
    
    # 计算中间变量
    an_val = (an - d) / (a1 - d)
    
    a = f[n-2]
    b = f[n-1]
    
    # 根据n的奇偶性计算k
    if n % 2 == 0:
        k = (an_val + a) / b
    else:
        k = (a - an_val) / b
    
    a = f[m-2]
    b = f[m-1]
    
    # 根据m的奇偶性计算kk
    if m % 2 == 0:
        kk = k * b - a
    else:
        kk = a - k * b
    
    # 计算最终结果
    ans = (a1 - d) * kk + d
    print(f"{ans:.3f}")

if __name__ == "__main__":
    main()