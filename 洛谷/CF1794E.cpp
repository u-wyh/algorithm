#include<bits/stdc++.h>
using namespace std;
#define int long long
const int BASE = 499;
const int MOD = 1e9+7;
const int MOD2 = 998244353;
const int MAXN = 2e5+5;

int n;
int nums[MAXN];
int hashval;
int hashval2;

set<int>s;
set<int>s2;

int p[MAXN];
int p2[MAXN];
int h[MAXN];
int h2[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int ans[MAXN];
int len;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    h[u]=1;
    h2[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        h[u]=(h[u]+h[v]*BASE)%MOD;
        h2[u]=(h2[u]+h2[v]*BASE)%MOD2;
    }
}

void dfs2(int u,int fa){
    if(fa!=0){
        h[u]=(((h[fa]-(h[u]*BASE)%MOD+MOD)%MOD)*BASE+h[u])%MOD;
        h2[u]=(((h2[fa]-(h2[u]*BASE)%MOD2+MOD2)%MOD2)*BASE+h2[u])%MOD2;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
    }
}

signed main()
{
    n=read();
    p[0]=1;
    p2[0]=1;
    s2.insert(1);
    s.insert(1);
    for(int i=1;i<=n;i++){
        p[i]=(p[i-1]*BASE)%MOD;
        p2[i]=(p2[i-1]*BASE)%MOD2;
        s.insert(p[i]);
        s2.insert(p2[i]);
    }
    for(int i=1;i<n;i++){
        nums[i]=read();
        hashval=(hashval+p[nums[i]])%MOD;
        hashval2=(hashval2+p2[nums[i]])%MOD2;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        int diff=(h[i]-hashval+MOD)%MOD;
        int diff2=(h2[i]-hashval2+MOD2)%MOD2;
        if(s.find(diff)!=s.end()&&s2.find(diff2)!=s2.end()){
            ans[++len]=i;
        }
    }
    printf("%lld\n",len);
    for(int i=1;i<=len;i++){
        printf("%lld ",ans[i]);
    }
    return 0;
}