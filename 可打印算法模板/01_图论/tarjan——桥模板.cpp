// 用途：Tarjan 求无向图的桥。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 例题：https://www.luogu.com.cn/problem/P1656
// 原代码：P1656.cpp；仅统一无向边的输出端点顺序。
// 题意：找出删除后会使无向图连通块增加的边。
// 思路：DFS 求 dfn/low；树边满足 low[子] > dfn[父] 即为桥。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;
const int MAXM = 5005;

int n,m;
vector<pair<int,int>>bridges;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];//记录这条边的编号

void addedge(int u,int v,int i){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=i;
    head[u]=cnt++;
}

void tarjan(int u,int id){
    //表示当前来到了点u  是通过真实编号id这条边来的
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!dfn[v]){
            tarjan(v,w);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                // 输出无向边时统一小点在前，便于最终按端点排序。
                bridges.push_back({min(u,v),max(u,v)});
            }
        }
        else if(w!=id){
            //不能走回头路  其实也就是为了防止走上父亲的点
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v,i);
        addedge(v,u,i);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    sort(bridges.begin(), bridges.end());
    for (auto &p : bridges) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
