#include<bits/stdc++.h>
using namespace std;
const int MAXN = 501;
const int MAXM = 501;

int n,m,a,b;
struct coord{
    int x,y;
};
queue<coord>q;
int ans[MAXN][MAXN];;
coord t[100005];
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
    cin>>n>>m>>a>>b;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans[i][j]=-1;
        }
    }
    for(int i=1;i<=a;i++){
        int x,y;
        cin>>x>>y;
        q.push({x,y});
        ans[x][y]=0;
    }
    for(int i=1;i<=b;i++){
        cin>>t[i].x>>t[i].y;
    }
    while(!q.empty()){
        coord u=q.front();
        int ux=u.x,uy=u.y;
        q.pop();
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            int d=ans[ux][uy];
            if(x<=0||x>n||y<=0||y>m||ans[x][y]!=-1)
                continue;
            ans[x][y]=d+1;
            q.push({x,y});
        }
    }
    for(int i=1;i<=b;i++){
        cout<<ans[t[i].x][t[i].y]<<endl;
    }
    return 0;
}
