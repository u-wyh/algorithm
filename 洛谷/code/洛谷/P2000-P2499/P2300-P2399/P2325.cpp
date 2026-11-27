// https://www.luogu.com.cn/problem/P2325
// 题意：将 N 个城市的树划分为若干省，每省大小在 [B, 3B] 之间，
// 每省选一个省会（可在省外）。
// 要求省内任意城市到省会路径上的城市（除省会外）均属于该省。
// 无解输出 0；
// 否则输出省数 K、各城市所属省编号及 K
// 个省会编号（Special Judge）。
// 数据范围：1 <= B <= N <= 10^3。
// 算法标签：树分块、深度优先搜索、栈
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,b;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int cap[MAXN];
int bel[MAXN];
int cntb;

int sta[MAXN];
int sz;

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    int x=sz;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        if(sz-x>=b){
            cap[++cntb]=u;
            while(sz!=x){
                bel[sta[sz--]]=cntb;
            }
        }
    }
    sta[++sz]=u;
}

int main()
{
    cin>>n>>b;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    if(cntb==0){
        cap[++cntb]=1;
    }
    while(sz>0){
        bel[sta[sz--]]=cntb;
    }
    cout<<cntb<<endl;
    for(int i=1;i<=n;i++){
        cout<<bel[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=cntb;i++){
        cout<<cap[i]<<' ';
    }
    return 0;
}