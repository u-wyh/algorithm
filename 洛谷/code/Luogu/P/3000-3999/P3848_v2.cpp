#include <bits/stdc++.h>
using namespace std;

int n,i,j,k,ans;
int m[105][105],f[105][105];
int dx[4]={-1,1,0,0},dy[4]={0,0,1,-1};

void dfs(int x,int y,int step){
	int i;
	ans=max(ans,step);
    for(i=0;i<4;i++){
        int tx=x,ty=y,s=0;
        while(tx+dx[i]>0 && tx+dx[i]<=n && ty+dy[i]>0 && ty+dy[i]<=n){
			tx+=dx[i];
			ty+=dy[i];
			s++;
            if(m[tx][ty]==0) break;
        }
        if(tx>0 && tx<=n && ty>0 && ty<=n && f[tx][ty]==0 && m[tx][ty]==0 && s!=1) {
            f[tx][ty]=1;
            dfs(tx,ty,step+s);
            f[tx][ty]=0;
        }
    }
}

int main()
{
    int x,y,i,j;
	cin>>n>>x>>y;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>m[i][j];

    f[x][y]=1;
    dfs(x,y,0);
    cout<<ans<<endl;
    return 0;
}
