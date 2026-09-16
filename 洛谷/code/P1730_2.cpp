#include<bits/stdc++.h>
using namespace std;

int n,m,q;
int dis[55][55][1005];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                dis[j][k][i]=1e8;
            }
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        dis[u][v][1]=min(dis[u][v][1],w);
    }
    for(int l=2;l<=m;l++){
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(dis[i][j][l]>dis[i][k][l-1]+dis[k][j][1]){
                        dis[i][j][l]=dis[i][k][l-1]+dis[k][j][1];
                    }
                }
            }
        }
    }
    scanf("%d",&q);
    while(q--){
        int x,y;
        scanf("%d %d",&x,&y);
        double ans=1e8,minans=1e8;
        for(int l=1;l<=n;l++){
            if(dis[x][y][l]<1e8){
                ans=(double)dis[x][y][l]/l;
            }
            minans=min(ans,minans);
        }
        if(minans==1e8){
            printf("OMG!\n");
        }
        else{
            printf("%.3lf\n",minans);
        }
    }
    return 0;
}
