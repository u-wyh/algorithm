// https://www.luogu.com.cn/problem/B3647
// 题意：给 n 个点、m 条边的带权无向连通图，可能有重边。
// 输出 n 行 n 列，第 i 行第 j 列是 i 到 j 的最短距离。
// 数据范围：n ≤ 100，m ≤ 4500，
// 边权 w 为整数且 1 ≤ w ≤ 1000。
// 算法标签：Floyd、最短路

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 5000;

int n,m,ans;
int dis[MAXN][MAXN];

void build() {
    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = INT_MAX;
            if(i==j)
                dis[i][j]=0;
        }
    }
}

void floyd() {
    // O(N^3)的过程
    // 枚举每个跳板
    // 注意，跳板要最先枚举！跳板要最先枚举！跳板要最先枚举！
    for (int bridge = 1; bridge <= n; bridge++) { // 跳板
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // i -> .....bridge .... -> j
                // distance[i][j]能不能缩短
                // distance[i][j] = min ( distance[i][j] , distance[i][bridge] + distance[bridge][j])
                if (dis[i][bridge] != INT_MAX
                        && dis[bridge][j] != INT_MAX
                        && dis[i][j] > dis[i][bridge] + dis[bridge][j]) {
                    dis[i][j] = dis[i][bridge] + dis[bridge][j];
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
        dis[v][u]=min(dis[v][u],w);
    }
    floyd();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<dis[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}

