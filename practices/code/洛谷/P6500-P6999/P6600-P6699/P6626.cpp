// https://www.luogu.com.cn/problem/P6626
// 题意：T 组数据，每组给定一棵 n 个点的树和 m 次独立询问 (x, k)：
// 第 0 天 x 收到消息，此后每天每个已收到消息的人会传给所有直接相连的人
// 求第 k 天新收到消息的人数。
// 数据范围：1 <= T <= 5，1 <= n, m <= 10^5，
// 1 <= x <= n，0 <= k < n。
// 难度评分：2300（洛谷分级换算）
// 算法标签：点分治、深度优先搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n ,m;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];
int cntq=1;

bool vis[MAXN];
int sz[MAXN];

int ans[MAXN];

int nodecnt[MAXN];
int maxedge;
int need[MAXN];
int qid[MAXN];
int cnta;

void prepare(){
    cntg=1,cntq=1;
    for(int i=1;i<=n;i++){
        headg[i]=0;
        headq[i]=0;
        vis[i]=false;
    }
    for(int i=1;i<=m;i++){
        ans[i]=false;
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

inline void addedge(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

inline void addedgeq(int u,int v,int id){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=id;
    headq[u]=cntq++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=headg[u];i;i=nxtg[i]){
            int v=tog[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int edge){
    nodecnt[edge]++;
    maxedge=max(maxedge,edge);
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int id=idq[i];
        if(v>=edge){
            ++cnta;
            need[cnta]=v-edge;
            qid[cnta]=id;
        }
    }
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,edge+1);
        }
    }
}

void calc(int u,int edge,int effect){
    cnta=0;
    maxedge=0;
    dfs(u,0,edge);
    for(int i=1;i<=cnta;i++){
        ans[qid[i]]+=nodecnt[need[i]]*effect;
    }
    for(int v=0;v<=maxedge;v++){
        nodecnt[v]=0;
    }
}

void compute(int u){
    vis[u]=true;
    calc(u,0,1);
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(!vis[v]){
            calc(v,1,-1);
            compute(getcentroid(v,u));
        }
    }
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        prepare();
        for(int i=1;i<n;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            addedge(v,u);
        }
        for(int i=1;i<=m;i++){
            int u,k;
            u=read(),k=read();
            addedgeq(u,k,i);
        }
        compute(getcentroid(1,0));
        for(int i=1;i<=m;i++){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}