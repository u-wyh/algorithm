# https://www.luogu.com.cn/problem/P3904
# 题意：输入小猪数量 n 和房间数量 m，
# 求将 n 只不同的小猪分配到 m 个相同的房间中
# 且没有房间空闲的方案数（即第二类斯特林数 S(n, m)）。
# 数据范围：1 <= n, m <= 50（答案可能很大，需高精度）。
# 难度评分：1500（洛谷分级换算）
# 算法标签：动态规划、组合数学
n,m=map(int,input().split())
dp=[ [0] * (m+1) for _ in range(n+1)]

dp[1][1]=1

for i in range(2,n+1):
    for j in range(1,min(i,m)+1):
        dp[i][j]=dp[i-1][j-1]+dp[i-1][j]*j

print(dp[n][m])