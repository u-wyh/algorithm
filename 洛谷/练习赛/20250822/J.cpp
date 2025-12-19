#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MOD = 998244353;

int n,m;
int nums[MAXN];

int fa[MAXN];
int sz;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    sz=n;
    int ans=0;
    int t=(m*(m-1)/2)%MOD;
    for(int i=1;i<=n;i++){
        int fx=find(i);
        int fy=find(nums[i]);
        if(fx!=fy){
            ans+=t*power(m,sz-2)%MOD;
            sz--;
            fa[fx]=fy;
        }
    }
    // ans--;
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}