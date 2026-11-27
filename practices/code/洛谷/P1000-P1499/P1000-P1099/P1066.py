# https://www.luogu.com.cn/problem/P1066
# 题意：给定 k 和 w，求满足以下条件的不同 2^k 进制数 r 的个数：
# 题意：1. r 至少为 2 位的 2^k 进制数（不含前导 0）。
# 题意：2. r 除末位外，每一位严格小于其右边相邻的一位。
# 题意：3. r 转为二进制数 q 后总位数不超过 w。
# 输入：一行输入两个正整数 k 和 w。
# 输出：一行输出方案总数（十进制高精度正整数，不超过 200 位，无前导零）。
# 数据范围：1 <= k <= 9。
# 数据范围：1 <= w <= 3 * 10^4。
# 算法标签：记忆化搜索
def main():
    
    k, w = map(int, input().split())
    m = (1 << k) - 1
    n = w // k
    res = w % k
    
    if res != 0:
        n += 1
    
    memo = {}
    
    def dfs(u, current_k):
        if u == 1:
            return 1
        if (u, current_k) in memo:
            return memo[(u, current_k)]
        total = 0
        for i in range(current_k + 1, m + 1):
            total += dfs(u - 1, i)
        memo[(u, current_k)] = total
        return total
    
    ans = 0
    
    # Handle full segments
    if res == 0:
        for len_ in range(2, n + 1):
            for i in range(1, m + 1):
                ans += dfs(len_, i)
    else:
        # Handle partial segment case
        partial_max = (1 << res) - 1
        for i in range(1, partial_max + 1):
            ans += dfs(n, i)
        
        # Handle full length segments
        for len_ in range(2, n):
            for i in range(1, m + 1):
                ans += dfs(len_, i)
    
    print(ans)

if __name__ == "__main__":
    main()