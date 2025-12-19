n,m=map(int,input().split())
dp=[ [0] * (m+1) for _ in range(n+1)]

dp[1][1]=1

for i in range(2,n+1):
    for j in range(1,min(i,m)+1):
        dp[i][j]=dp[i-1][j-1]+dp[i-1][j]*j

print(dp[n][m])