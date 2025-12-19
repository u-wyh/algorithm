#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,m;
int dep[MAXN];
int val[MAXN];
int fa[MAXN];

vector<int>vec[MAXN];
int in[MAXN];
// bool vis[MAXN];
bitset<MAXN>ans;
bitset<MAXN>bs[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
    }
}

void dfs2(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs2(v);
        if(dep[fa[v]]<=dep[fa[u]]){
            fa[u]=fa[v];
        }
    }
}

void dfs3(int u){
    bs[u].set(0);
    for(int i=0;i<(int)vec[u].size();i++){
        int v=vec[u][i];
        dfs3(v);
        bitset<MAXN>tmp=bs[u];
        for(int j=0;j<=val[v];j++){
            if(bs[v].test(j)){
                bs[u]|=(tmp<<j);
            }
        }
        val[u]+=val[v];
    }
    bs[u].set(val[u]);
    ans|=bs[u];
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        fa[i]=i;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        in[v]++;
    }
    int root=1;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            root=i;
            break;
        }
    }
    dfs1(root,0);
    m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        if(dep[v]<=dep[fa[u]]){
            fa[u]=v;
        }
    }
    dfs2(root);
    for(int i=1;i<=n;i++){
        int f=find(i);
        if(f!=i){
            val[f]+=val[i];
        }
    }
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int fx=find(u);
            int fy=find(v);
            if(fx==fy){
                continue;
            }
            vec[fx].push_back(fy);
        }
    }
    dfs3(root);
    int res=ans.count();
    cout<<res<<endl;
    return 0;
}