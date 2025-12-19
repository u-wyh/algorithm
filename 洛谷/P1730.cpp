#include<stdio.h>
using namespace std;
#define INF 1000000000
int n,m,q;
int dis[60][60][1010];
int main()
{
    int i,j,k,l;
    scanf("%d %d",&n,&m);//读入
    for(l=1;l<=m;l++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                dis[i][j][l]=INF;//初始化
    for(i=1;i<=m;i++)
    {
        long long a,b,w;
        scanf("%lld %lld %lld",&a,&b,&w);
        if(dis[a][b][1]>w)
            dis[a][b][1]=w;//注意有重边的情况
    }
    for(l=2;l<=m;l++)
        for(k=1;k<=n;k++)
            for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
                    if(dis[i][j][l]>dis[i][k][l-1]+dis[k][j][1])
                        dis[i][j][l]=dis[i][k][l-1]+dis[k][j][1];//类似Floyd算法的DP
    scanf("%d",&q);
    while(q--)
    {
        int x,y;
        double ans=INF,min=INF;
        scanf("%d %d",&x,&y);//读入询问
        for(l=1;l<=n;l++)
        {
            if(dis[x][y][l]<INF)
                ans=double(dis[x][y][l])/double(l);
            if(ans<min)
                min=ans;
        }//对边数进行枚举,算权值和/边数
        if(min==INF)
            printf("OMG!\n");
        else
            printf("%.3lf\n",min);//输出
    }
}
