MOD = 10**8

def multiply(a, b):
    n = len(a)
    m = len(b[0])
    k = len(a[0])
    ans = [[0] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            for p in range(k):
                ans[i][j] += a[i][p] * b[p][j]
                ans[i][j] %= MOD
    return ans

def power(a, p):
    n = len(a)
    base = [[0] * n for _ in range(n)]
    for i in range(n):
        base[i][i] = 1
    while p > 0:
        if p & 1:
            base = multiply(a, base)
        p >>= 1
        a = multiply(a, a)
    return base

def main():
    n = int(input())
    if n == 2:
        print(2)
        return
    a = [[2, 1]]
    base = [[1, 1], [1, 0]]
    a = multiply(a, power(base, n - 2))
    print(a[0][0])

if __name__ == "__main__":
    main()