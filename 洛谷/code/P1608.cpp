// https://www.luogu.com.cn/problem/P1608
// 题意：输入 N 个点、E 条单向边（可能有重边，无自环），每条边权为 C。
// 求从 1 号点到 N 号点的最短路径花费，以及经过点序列不同的最短路条数。
// 输出最短花费与方案总数；若无法到达输出 No answer。
// 数据范围：
// 1 <= N <= 2000（点数）
// 0 <= E <= N*(N-1)（边数，1 <= I, J <= N 且 I != J）
// 1 <= C <= 10（边权）
// 最短路总数不超过 2^30
#include<bits/stdc++.h>
// 算法标签：Floyd、最短路
using namespace std;
const int MAXN = 2005;

int n,m,ans;
int dis[MAXN][MAXN];
int path[MAXN][MAXN];

void build() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = INT_MAX;
        }
    }
}

void floyd() {
    for (int bridge = 1; bridge <= n; bridge++) { // 跳板
//        if(dis[1][bridge]>dis[1][n]||dis[bridge][n]>dis[1][n]){
//            continue;
//        }
        for (int i = 1; i <= n; i++) {
//            if(dis[1][i]>dis[1][n]||dis[i][n]>dis[1][n]){
//                continue;
//            }
            for (int j = 1; j <= n; j++) {
//                if(dis[1][j]>dis[1][n]||dis[j][n]>dis[1][n]){
//                    continue;
//                }
                if (dis[i][bridge] != INT_MAX
                        && dis[bridge][j] != INT_MAX
                        && dis[i][j] > dis[i][bridge] + dis[bridge][j]) {
                    dis[i][j] = dis[i][bridge] + dis[bridge][j];
                    path[i][j]=path[i][bridge]*path[bridge][j];
                }
                else if (dis[i][bridge] != INT_MAX
                        && dis[bridge][j] != INT_MAX
                        && dis[i][j] == dis[i][bridge] + dis[bridge][j]) {
                    path[i][j]+=path[i][bridge]*path[bridge][j];
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=min(dis[u][v],w);
        path[u][v]=1;
    }
    floyd();
    if(dis[1][n]==INT_MAX){
        cout<<"No answer"<<endl;
        return 0;
    }
    cout<<dis[1][n]<<' '<<path[1][n]<<endl;
    return 0;
}
