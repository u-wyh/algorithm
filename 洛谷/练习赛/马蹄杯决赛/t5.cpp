#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+1;

int n;
int val[MAXN];
bitset<MAXN>bs[MAXN];
bitset<MAXN>up[MAXN];
int son[MAXN];//记录自己是父亲的第几个儿子
int sz[MAXN];//记录每个节点有多少个儿子
vector<bitset<MAXN>>pre[MAXN];
vector<bitset<MAXN>>suf[MAXN];
int ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void dfs1(int u,int fa){
    pre[u].push_back(bitset<MAXN>());
    suf[u].push_back(bitset<MAXN>());
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]++;
            son[v]=sz[u];
            pre[u].push_back(bs[v]);
            suf[u].push_back(bs[v]);
        }
    }
    for(int i=2;i<=sz[u];i++){
        pre[u][i]|=pre[u][i-1];
    }
    for(int i=sz[u]-1;i>=1;i--){
        suf[u][i]|=suf[u][i+1];
    }
    if(val[u]==1){
        bs[u].set(0);
    }
    bs[u]|=(pre[u][sz[u]]<<1);
}

inline void dfs2(int u,int fa){
    if(fa!=0){
        bitset<MAXN>tmp;
        if(son[u]!=sz[fa]){
            tmp=pre[fa][son[u]-1]|suf[fa][son[u]+1];
        }
        else{
            tmp=pre[fa][son[u]-1];
        }

        tmp<<=2;
        if(val[fa]==1){
            tmp.set(1);
        }
        up[u]=(up[fa]<<1)|tmp;
    }

    ans[u]=(up[u]|bs[u]).count();
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs2(v,u);
        }
    }
}

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
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
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
        printf("%d\n",ans[i]);
    }
    return 0;
}