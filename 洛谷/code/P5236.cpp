// 仙人掌最短路，C++版
// 给定n个点、m条边的仙人掌图，每条边有边权，没有自环，没有重边
// 一共q条查询，每条查询格式为 x y，查询点x和点y之间的最短路距离
// 1 <= n、q <= 10^4
// 1 <= m <= 2 * 10^4
// 1 <= 边权 <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P5236
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这里的圆方树建图方式和正常的是不太一样的
// 就是割边不在直接建立一个方点  这样与二元环区分开
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXM = 4e4+5;

int n,m,q;

int head1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int weight1[MAXM];
int cntg1=2;

int head2[MAXN];
int nxt2[MAXM];
int to2[MAXM];
int weight2[MAXM];
int cntg2=1;

int cntn;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int stasz;

int fromweight[MAXN];
int cyclelen[MAXN];
int cyclesum[MAXN];

int fa[MAXN];
int son[MAXN];
int dep[MAXN];
int sz[MAXN];
int top[MAXN];
int len[MAXN];

void addedge1(int u,int v,int w){
    nxt1[cntg1]=head1[u];
    to1[cntg1]=v;
    weight1[cntg1]=w;
    head1[u]=cntg1++;
}

void addedge2(int u,int v,int w){
    nxt2[cntg2]=head2[u];
    to2[cntg2]=v;
    weight2[cntg2]=w;
    head2[u]=cntg2++;
}

void cyclelink(int u,int v){
    cntn++;
    cyclesum[cntn]=fromweight[u];
    addedge2(u,cntn,0);
    int tmp=stasz;
    int pop;
    do{
        pop=sta[tmp--];
        cyclelen[pop]=cyclesum[cntn];
        cyclesum[cntn]+=fromweight[pop];
    }while(pop!=v);
    do{
        pop=sta[stasz--];
        addedge2(cntn,pop,min(cyclelen[pop],cyclesum[cntn]-cyclelen[pop]));
    }while(pop!=v);
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++stasz]=u;
    for(int i=head1[u];i;i=nxt1[i]){
        if((i^1)==preedge){
            continue;
        }

        int v=to1[i];
        int w=weight1[i];
        if(dfn[v]==0){
            tarjan(v,i);
            fromweight[v]=w;
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
            }
            else if(low[v]>dfn[u]){
                stasz--;
                addedge2(u,v,w);
            }
            else{
                cyclelink(u,v);
            }
        }
        else if(dfn[v]<dfn[u]){
            fromweight[v]=w;
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void dfs1(int u,int f,int l){
    sz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    len[u]=l;
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        int w=weight2[i];
        if(v!=f){
            dfs1(v,u,l+w);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

int lca(int a,int b){
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]){
            b=fa[top[b]];
        }
        else{
            a=fa[top[a]];
        }
    }
    return dep[a]<dep[b]?a:b;
}

int find(int x,int square){
    int pre=0;
    while(top[x]!=top[square]){
        pre=top[x];
        x=fa[top[x]];
    }
    return x==square?pre:son[square];
}

int query(int x,int y){
    int ans=0;
    int xylca=lca(x,y);
    if(xylca<=n){
        return len[x]+len[y]-len[xylca]*2;
    }
    else{
        int fx=find(x,xylca);
        int fy=find(y,xylca);
        ans=len[x]+len[y]-len[fx]-len[fy];
        int sml=min(cyclelen[fx],cyclelen[fy]);
        int big=max(cyclelen[fx],cyclelen[fy]);
        ans+=min(big-sml,cyclesum[xylca]-big+sml);
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m>>q;
    cntn=n;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge1(u,v,w);
        addedge1(v,u,w);
    }

    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            tarjan(i,0);
        }
    }

    dfs1(1,0,0);
    dfs2(1,1);

    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        cout<<query(x,y)<<endl;
    }
    return 0;
}