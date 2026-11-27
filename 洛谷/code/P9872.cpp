// https://www.luogu.com.cn/problem/P9872
// 题意：多组数据（共 T 组）。
// 给定以 1 为根的 n 个节点的树，子节点遍历顺序任意
// 对每个节点 i ∈ [1, n] 求其在所有可能的 DFS 序中出现位置的最小值与最大值（位置从 1 开始计数）。
// 题意：第一行输入 T，每组输入 n 及 n-1 行 (x, y)（x 是 y 的父节点）；每组输出 n 行，每行两个整数。
// 数据范围：1 <= T <= 10^6，1 <= n <= 10^5，sum(n) <= 10^6。
// 算法标签：树形动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int earlist[MAXN];
int lastest[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int n;
int sz[MAXN];

void build(){
    cnt=1;
    fill(earlist+1,earlist+n+1,0);
    fill(lastest+1,lastest+n+1,0);
    fill(head+1,head+n*2+1,0);
    fill(Next+1,Next+2*n+1,0);
    fill(to+1,to+2*n+1,0);
    fill(sz+1,sz+n+1,0);
}

void dfs1(int u,int f){
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
}

void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            earlist[v]=earlist[u]+1;
            lastest[v]=lastest[u]+sz[u]-sz[v];
            dfs2(v,u);
        }
    }
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        build();
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;

            Next[cnt]=head[u];
            to[cnt]=v;
            head[u]=cnt++;

            Next[cnt]=head[v];
            to[cnt]=u;
            head[v]=cnt++;
        }
        dfs1(1,0);
        earlist[1]=1;
        lastest[1]=1;
        dfs2(1,0);
        for(int i=1;i<=n;i++){
            cout<<earlist[i]<<' '<<lastest[i]<<endl;
        }
    }
    return 0;
}
