// 用途：用 Floyd 预处理全源最短路，计算指定访问顺序的最短总路程。
// 时间：O(n³)。
// 空间：O(n²)。
// 注意：输入完整邻接矩阵及经过的点序列；n<=100，m<=10000。
// 例题：https://www.luogu.com.cn/problem/P2910
// 题意：按给定顺序访问地点，求各段最短路之和。
// 思路：Floyd 预处理任意两点最短路，再按访问顺序累加。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

const long long INF = LLONG_MAX / 4;
int n,m;
long long ans, dis[MAXN][MAXN];
int path[MAXM];

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = INF;
        }
    }
}

void floyd() {
    // O(N^3)的过程
    // 枚举每个跳板
    // 注意，跳板要最先枚举！跳板要最先枚举！跳板要最先枚举！
    for (int bridge = 0; bridge < n; bridge++) { // 跳板
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // i -> .....bridge .... -> j
                // distance[i][j]能不能缩短
                // distance[i][j] = min ( distance[i][j] , distance[i][bridge] + distance[bridge][j])
                if (dis[i][bridge] != INF
                        && dis[bridge][j] != INF
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
    //build();
    //正常情况下，是需要我们自己建立邻接矩阵的
    for(int i=1;i<=m;i++){
        cin>>path[i];
        path[i]--;
        //注意下标的对应
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>dis[i][j];
            //这道题直接给出来邻接矩阵  不需要我们建立
        }
    }
    floyd();
    for(int i=1;i<m;i++){
        ans+=dis[path[i]][path[i+1]];
    }
    cout<<ans;
    return 0;
}
