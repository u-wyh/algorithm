// https://www.luogu.com.cn/problem/P2888
// 题意：输入站点数 N、单向路径数 M、任务数 T，M 条有向边 (S_i -> E_i，最高栏高 H_i)，以及 T 个起终点任务 (A_i, B_i)。
// 对每个任务，寻找一条从站点 A_i 到站点 B_i 的有向路径，使得路径上所跨过的最高栏的高度最小。
// 依次计算所有任务的最优瓶颈高度。
// 输出共 T 行，第 i 行为对应任务路径最高栏高的最小值；若无法到达则输出 -1。
// 数据范围：对于 100% 的数据，1 <= N <= 300，1 <= M <= 2.5*10^4，1 <= H_i <= 10^6
// 1 <= T <= 4*10^4，1 <= A_i, B_i <= N。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int MAXM = 25005;

int n,m,t;
int dis[MAXN][MAXN];

void build() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = INT_MAX;
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
                    && dis[bridge][j] != INT_MAX) {
                    dis[i][j] = min(max(dis[i][bridge],dis[bridge][j]),dis[i][j]);
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m>>t;
    build();

    int x,y,z;
    for(int i=1;i<=m;i++){
        cin>>x>>y>>z;
        dis[x][y]=z;
    }
    floyd();
    for(int i=1;i<=t;i++){
        int a,b;
        cin>>a>>b;
        if(dis[a][b]==INT_MAX){
            dis[a][b]=-1;
        }
        cout<<dis[a][b]<<endl;
    }
    return 0;
}
