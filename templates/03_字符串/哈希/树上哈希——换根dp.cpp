// https://www.luogu.com.cn/problem/P4323
// 这种哈希用的是质数来减少碰撞
// h[x] = 1 + ∑h[y] * p[siz[y]]
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 1300005;//这个范围内存在1e5个质数   用于欧拉筛
const int MAXN = 1e5+25;

int n;

set<long long>s;

//两个树的哈希数组
long long f[MAXN];
long long g[MAXN];
int sz[MAXN];

//记录第二颗树上的各个节点的入度  以及所有的叶子结点
int in[MAXN];
int leaf[MAXN];
int len;

bool vis[MAXM];
int prime[MAXN];
int cntt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int head1[MAXN];
int nxt1[MAXN<<1];
int to1[MAXN<<1];
int cnt1=1;

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

void euler(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cntt]=i;
        }
        for(int j=1;j<=cntt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void Addedge(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

//用于求第一个树的各个节点为根的哈希值
void dfs1(int u,int fa){
    sz[u]=1;
    f[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        f[u]+=1ll*prime[sz[v]]*f[v];
    }
}

void dfs2(int u,int fa){
    if(fa!=0){
        f[u]=f[u]+1ll*prime[n-sz[u]]*(f[fa]-f[u]*prime[sz[u]]);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
    }
}

//用于求第二个树的各个节点为根的哈希值
void dfs3(int u,int fa){
    sz[u]=1;//复用sz数组
    g[u]=1;
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs3(v,u);
        sz[u]+=sz[v];
        g[u]+=1ll*prime[sz[v]]*g[v];
    }
}

void dfs4(int u,int fa){
    if(fa!=0){
        g[u]=g[u]+1ll*prime[n+1-sz[u]]*(g[fa]-g[u]*prime[sz[u]]);//注意这里有n+1个点
    }
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs4(v,u);
    }
}

signed main()
{
    //求出质数数组  准备哈希
    euler(MAXM-1);
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        int u,v;
        u=read(),v=read();
        in[u]++,in[v]++;
        Addedge(u,v);
        Addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    //在集合中插入所有哈希值
    for(int i=1;i<=n;i++){
        s.insert(f[i]);
    }
    //统计叶子结点
    for(int i=1;i<=n;i++){
        if(in[i]==1){
            leaf[++len]=i;
        }
    }
    dfs3(1,0);
    dfs4(1,0);

    int ans=n;
    for(int t=1;t<=len;t++){
        int u=leaf[t];
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            long long val=g[v]-prime[1];
            if(s.find(val)!=s.end()){
                ans=min(ans,u);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}