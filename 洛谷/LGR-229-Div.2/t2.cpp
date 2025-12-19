#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,m;
int d[MAXN];
int t[MAXN];

int f[MAXN];
int g[MAXN];

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

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        d[i]=read();
    }
    sort(d+1,d+n+1);
    for(int i=1;i<=n;i++){
        f[i]=f[i-1]+d[i];
    }
    for(int i=1;i<=n;i++){
        g[i]=g[i-1]+f[i];
        // cout<<g[i]<<' ';
    }
    // cout<<endl;
    while(m--){
        int t=read();
        int l=0,r=n,ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            if(g[mid]<=t){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}