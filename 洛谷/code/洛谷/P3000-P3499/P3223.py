# https://www.luogu.com.cn/problem/P3223
# 题意：输入男生人数 n 和女生人数 m（另有 2 名老师）。
# 将 n 名男生、m 名女生和 2 名老师排成一排，所有人互不相同，
# 要求任意两名女生不相邻且两名老师也不相邻。
# 输出满足条件的总排列数（高精度，无取模）。
# 数据范围：0 <= n <= 2000，0 <= m <= 2000。
# 算法标签：组合数学
n,m=map(int,input().split())
if n==0 and m==0:
    print(0)
elif m-1>n+2:
    print(0)
else:
    ans=1
    for i in range(1,n+3):
        ans*=i
    for i in range(1,m+1):
        ans*=i
    for i in range(1,m+1):
        ans*=(n+4-i)
        ans/=i
    res=2
    for i in range(1,n+2):
        res*=i
    for i in range(1,m+1):
        res*=i
    for i in range(1,m+1):
        res*=(n+3-i)
        res/=i
    print(int(ans-res))