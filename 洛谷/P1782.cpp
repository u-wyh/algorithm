#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = 1e4+5;

int n,m,c;
struct node{
    int val,cost;
}nums[MAXN];
int cnt;

int f[MAXM];
int g[MAXM];

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
    n=read(),m=read(),c=read();
    for(int i=1;i<=n;i++){
        int v,w,d;
        v=read(),w=read(),d=read();
        for(int i=1;i<=d;i*=2){
            if(w*i>c){
                break;
            }
            nums[++cnt].val=w*i;
            nums[cnt].cost=v*i;
            d-=i;
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=c;j>=nums[i].cost;j--){
            f[j]=max(f[j],f[j-nums[i].cost]+nums[i].val);
        }
    }
    // for(int i=1;i<=c;i++){
    //     f[i]=max(f[i],f[i-1]);
    // }
    for(int i=1;i<=m;i++){
        int a,b,d;
        a=read(),b=read(),d=read();
        for(int j=c;j>=0;j--){
            for(int k=0;k<=j;k++){
                f[j]=max(f[j],f[j-k]+a*k*k+b*k+d);
            }
        }
    }
    cout<<f[c]<<endl;
    // for(int i=1;i<=c;i++){
    //     g[i]=max(g[i],g[i-1]);
    // }
    // int ans=INT_MIN;
    // for(int i=0;i<=c;i++){
    //     ans=max(ans,f[i]+g[c-i]);
    // }
    // cout<<ans<<endl;
    return 0;
}