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
