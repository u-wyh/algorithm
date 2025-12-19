#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;
const int MAXM = 305;
const int INF = 1e9;

int n,m,v,e;
int dis[MAXM][MAXM];
int a[MAXN],b[MAXN];
double c[MAXN];
double dp[MAXN][MAXN][2];

void floyd(){
    for(int k=1;k<=v;k++){
        for(int i=1;i<=v;i++){
            for(int j=1;j<=v;j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}

int main()
{
    scanf("%d %d %d %d",&n,&m,&v,&e);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%lf",&c[i]);
    }
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            dis[i][j]=INF;
        }
        dis[i][i]=0;
    }
    for(int i=1;i<=e;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=dis[u][v];
    }
    floyd();
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][0]=dp[i][j][1]=INF;
        }
    }
    dp[1][0][0]=0;
    dp[1][1][1]=0;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=min(i,m);j++){
            double t1,t2;
            t1=dp[i-1][j][0]+dis[a[i-1]][a[i]];
            t2=dp[i-1][j][1]+(1-c[i-1])*dis[a[i-1]][a[i]]+c[i-1]*dis[b[i-1]][a[i]];
            dp[i][j][0]=min(t1,t2);

            if(j==0){
                continue;
            }
            t1=dp[i-1][j-1][0]+(1-c[i])*dis[a[i-1]][a[i]]+c[i]*dis[a[i-1]][b[i]];
            t2=dp[i-1][j-1][1]+(1-c[i])*((1-c[i-1])*dis[a[i-1]][a[i]]+c[i-1]*dis[b[i-1]][a[i]])+c[i]*((1-c[i-1])*dis[a[i-1]][b[i]]+c[i-1]*dis[b[i-1]][b[i]]);
            dp[i][j][1]=min(t1,t2);
        }
    }
    double ans=INF;
    for(int i=0;i<=m;i++){
        ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
    }
    printf("%.2lf\n",ans);
    return 0;
}