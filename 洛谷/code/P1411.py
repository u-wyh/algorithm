import sys
sys.setrecursionlimit(10000)

def main():
    n = int(sys.stdin.readline().strip())
    graph = [[] for _ in range(n + 1)]
    
    # 读取边并构建图
    for _ in range(n - 1):
        u, v = map(int, sys.stdin.readline().split())
        graph[u].append(v)
        graph[v].append(u)
    
    # dp[u][j] 表示以u为根的子树中，除了包含u的大小为j的连通块之外的其他连通块的最大贡献
    # dp[u][0] 存储整个子树的最大分数
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    size = [0] * (n + 1)
    
    def dfs(u, parent):
        size[u] = 1
        # 初始化：不切任何边时，包含u的连通块大小为1，其他连通块贡献为1（乘积单位元）
        dp[u][1] = 1
        
        for v in graph[u]:
            if v == parent:
                continue
                
            dfs(v, u)
            
            # 临时数组，用于更新dp值
            temp = [0] * (size[u] + 1)
            for j in range(size[u] + 1):
                temp[j] = dp[u][j]
            
            # 更新子树大小
            old_size = size[u]
            size[u] += size[v]
            
            # 初始化新的dp值
            for j in range(size[u] + 1):
                dp[u][j] = 0
            
            # 背包DP：考虑是否切断u-v边
            # 从大到小遍历，避免重复计算
            for j in range(old_size, 0, -1):
                if temp[j] == 0:
                    continue
                
                # 情况1：切断u-v边，v子树独立
                # v子树的贡献是dp[v][0]（整个v子树的最大分数）
                cut_value = temp[j] * dp[v][0]
                if cut_value > dp[u][j]:
                    dp[u][j] = cut_value
                
                # 情况2：不切断u-v边，合并连通块
                for k in range(1, size[v] + 1):
                    if dp[v][k] == 0:
                        continue
                    
                    # 合并后包含u的连通块大小为j+k
                    merge_value = temp[j] * dp[v][k]
                    if j + k <= size[u] and merge_value > dp[u][j + k]:
                        dp[u][j + k] = merge_value
        
        # 计算整个子树的最大分数：考虑包含u的连通块的贡献
        dp[u][0] = 0
        for j in range(1, size[u] + 1):
            # 总分数 = 其他连通块贡献 * 包含u的连通块大小
            total = dp[u][j] * j
            if total > dp[u][0]:
                dp[u][0] = total
    
    dfs(1, 0)
    print(dp[1][0])

if __name__ == "__main__":
    main()