def multiply(a, b, mod):
    """矩阵乘法，结果对 mod 取模"""
    n = len(a)
    m = len(b[0])
    k = len(a[0])
    ans = [[0] * m for _ in range(n)]  # 初始化结果矩阵
    for i in range(n):
        for j in range(m):
            for p in range(k):
                ans[i][j] = (ans[i][j] + a[i][p] * b[p][j]) % mod
    return ans

def power(a, p, mod):
    """矩阵快速幂，结果对 mod 取模"""
    n = len(a)
    base = [[0] * n for _ in range(n)]  # 初始化单位矩阵
    for i in range(n):
        base[i][i] = 1
    while p:
        if p & 1:
            base = multiply(base, a, mod)
        p >>= 1
        a = multiply(a, a, mod)
    return base

def main():
    # 输入
    n, a, b, c, mod = map(int, input().split())
    
    # 初始化 nums 和 base 矩阵
    nums = [[1, 1, 1]]  # 1x3 矩阵
    base = [
        [a + b, 0, 0],
        [b, a + b, 0],
        [c, 0, 1]
    ]  # 3x3 矩阵
    
    # 计算 base 的 (n-1) 次幂
    base_pow = power(base, n - 1, mod)
    
    # 计算 nums * base^(n-1)
    result = multiply(nums, base_pow, mod)
    
    # 输出结果
    print(result[0][0])

if __name__ == "__main__":
    main()