#include<bits/stdc++.h>
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
    for (int bridge = 1; bridge <= n; bridge++) { // Ìø°å
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
