// https://www.luogu.com.cn/problem/P8435
// 题意：给定 n 点 m 边的无向图（可能含孤立点与自环），采用“不存在割点的极大连通子图”定义求所有点双连通分量的个数及每个分量包含的结点（分量及结点顺序任意）。
// 数据范围：100% 数据满足 1 <= n <= 5*10^5，1 <= m <= 2*10^6。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 4e6+5;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int sta[MAXN];
int top;

int vbccl[MAXN];
int vbccr[MAXN];
int vbccarr[MAXN<<1];
int vbcccnt;
int idx;

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[v],low[u]);
            if(low[v]>=dfn[u]){
                vbcccnt++;
                vbccl[vbcccnt]=idx+1;
                while(sta[top+1]!=v){
                    vbccarr[++idx]=sta[top--];
                }
                vbccarr[++idx]=u;
                vbccr[vbcccnt]=idx;
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(u==v){
            continue;
        }
        addedge(u,v);
        addedge(v,u);
    }

    for(int i=1;i<=n;i++){
        if(head[i]==0){
            vbccarr[++idx]=i;
            vbcccnt++;
            vbccl[vbcccnt]=vbccr[vbcccnt]=idx;
        }
        else if(dfn[i]==0){
            tarjan(i);
        }
    }

    cout<<vbcccnt<<endl;
    for(int i=1;i<=vbcccnt;i++){
        cout<<(vbccr[i]-vbccl[i]+1);
        for(int j=vbccl[i];j<=vbccr[i];j++){
            cout<<' '<<vbccarr[j];
        }
        cout<<endl;
    }
    return 0;
}