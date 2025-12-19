#include<bits/stdc++.h>
using namespace std;

int n,m,T;
char s[105][105];
int  nums[105][105],t[105][105];
int r1,c1,r2,c2;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int ans=0;
struct coord{
    int x,y;
};
queue<coord>Q;

void dfs(int x,int y,int time){
    if(time>T||t[x][y]>(T-time))
        return ;
    if(time==T){
        if(x==r2&&y==c2){
            ans++;
            return ;
        }
        else{
            return ;
        }
    }
    for(int k=0;k<4;k++){
        int ux=x+walk[k][0],uy=y+walk[k][1];
        if(ux<=0||uy<=0||ux>n||uy>m||nums[ux][uy]==0)
            continue;
        dfs(ux,uy,time+1);
    }
}

int main()
{
    memset(t,1e8,sizeof(t));
    cin>>n>>m>>T;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
            if(s[i][j]=='*')
                nums[i][j]=0;
            else
                nums[i][j]=1;
        }
    }
    cin>>r1>>c1>>r2>>c2;
    t[r2][c2]=0;
    Q.push({r2,c2});
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x>0 && x<=n && y>0 && y<=n && t[x][y]==1e8&&nums[x][y]==0&&(abs(x-r2)+abs(y-c2))<=T){
                t[x][y]=t[ux][uy]+1;
                Q.push({x,y});
            }
        }
    }
    dfs(r1,c1,0);
    printf("%d\n",ans);
    return 0;
}

