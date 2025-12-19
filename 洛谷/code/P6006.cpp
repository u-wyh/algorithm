#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 2e6+5;

int n,m;
int nums[MAXN];
int cnt[MAXM];
long long f[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }

    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cnt[nums[j]+1000000]=0;
        }
        for(int j=i+1;j<=n;j++){
            if((1000000-nums[i]-nums[j])>=0&&(1000000-nums[i]-nums[j])<=2000000)
                f[i][j]=cnt[1000000-nums[i]-nums[j]];
            cnt[1000000+nums[j]]++;
        }
    }

    for(int len=3;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            f[i][j]+=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
        }
    }
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        printf("%lld\n",f[l][r]);
    }
    return 0;
}