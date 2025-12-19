#include<bits/stdc++.h>
using namespace std;
#define MAX 2005

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,m,k;
char s[MAX];
int nums[MAX][MAX],d[MAX][MAX];
struct coord{
    int x,y;
};
queue<coord>Q;

int main()
{
    memset(d,-1,sizeof(d));
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[j];
            if(s[j]=='X')
                nums[i][j]=0;
            else
                nums[i][j]=1;
        }
    }
    Q.push({1,1});
    d[1][1]=0;
    while(!Q.empty()){
        coord u=Q.front();
        int ux=u.x,uy=u.y;
        if(ux==n&&uy==m)
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            int x=ux+walk[i][0],y=uy+walk[i][1];
            if(x==0||y==0||x>n||y>m||d[x][y]!=-1||nums[x][y]==0)
                continue;
            d[x][y]=d[ux][uy];
            if(i==1||i==3)
                d[x][y]++;
            Q.push({x,y});
        }
    }
    long long time[k+1],a[k+1],b[k+1],ans=1e18;
    int cnt=0;
    for(int i=1;i<=k;i++){
        cin>>a[i]>>b[i];
        time[i]=a[i]*(n+m-2+d[n][m])+b[i]*d[n][m];
        ans=min(ans,time[i]);
    }
    for(int i=1;i<=k;i++){
        if(time[i]==ans)
            cnt++;
    }
    printf("%lld %d\n",ans,cnt);
    return 0;
}
