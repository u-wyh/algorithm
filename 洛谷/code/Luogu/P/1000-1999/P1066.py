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