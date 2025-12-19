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