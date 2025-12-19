#include<bits/stdc++.h>
using namespace std;
#define int long long

int f[105][105];
int edge[105][105];
int n,m;
double ans[105];

void floyd() {
    for (int bridge = 1; bridge <= n; bridge++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][bridge] != INT_MAX && f[bridge][j] != INT_MAX && f[i][j] > f[i][bridge] + f[bridge][j]) {
                    f[i][j] = f[i][bridge] + f[bridge][j];
                    edge[i][j]=edge[i][bridge]*edge[bridge][j];
                }
                else if (f[i][bridge] != INT_MAX && f[bridge][j] != INT_MAX && f[i][j] == f[i][bridge] + f[bridge][j]) {
                    edge[i][j]+=edge[i][bridge]*edge[bridge][j];
                }
            }
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        f[u][v]=w,f[v][u]=w;
        edge[u][v]=1,edge[v][u]=1;
    }
    floyd();
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(k==i||k==j||i==j){
                    continue;
                }
                if(f[i][k]+f[k][j]==f[i][j]){
                    ans[k]+=(1.0*edge[i][k]*edge[k][j])/edge[i][j];
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%.3lf\n",ans[i]);
    }
    return 0;
}
