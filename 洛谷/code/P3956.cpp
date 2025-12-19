#include"cstdio"
#include"iostream"
#include"cmath"
#include"cstring"
using namespace std;

int map[1005][1005];
int f[1005][1005];
int m,n;

void dfs(int i,int j,int c,bool fl,int now){
    if(i>m||i<1||j<1||j>m)
        return;
    f[i][j]=now;//一种记忆化写法，不断更新(其实也相当于剪枝)
        //不用魔法
    if(now+abs(c-map[i-1][j])<f[i-1][j]&&map[i-1][j]!=-1)dfs(i-1,j,map[i-1][j],1,now+abs(c-map[i-1][j]));
    if(now+abs(c-map[i][j-1])<f[i][j-1]&&map[i][j-1]!=-1)dfs(i,j-1,map[i][j-1],1,now+abs(c-map[i][j-1]));
    if(now+abs(c-map[i+1][j])<f[i+1][j]&&map[i+1][j]!=-1)dfs(i+1,j,map[i+1][j],1,now+abs(c-map[i+1][j]));
    if(now+abs(c-map[i][j+1])<f[i][j+1]&&map[i][j+1]!=-1)dfs(i,j+1,map[i][j+1],1,now+abs(c-map[i][j+1]));
    if(fl==1)//用
    {
        if(now+2<f[i-1][j]&&map[i-1][j]==-1)dfs(i-1,j,c,0,now+2);
        if(now+2<f[i][j-1]&&map[i][j-1]==-1)dfs(i,j-1,c,0,now+2);
        if(now+2<f[i+1][j]&&map[i+1][j]==-1)dfs(i+1,j,c,0,now+2);
        if(now+2<f[i][j+1]&&map[i][j+1]==-1)dfs(i,j+1,c,0,now+2);
    }
    return;
}
int main()
{
    memset(map,-1,sizeof(map));
    scanf("%d%d",&m,&n);
    int x,y,c;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&x,&y,&c);
        map[x][y]=c;
    }
    memset(f,127,sizeof(f));//非常大的诡异值
    int s=f[m][m];
    dfs(1,1,map[1][1],1,0);
    if(f[m][m]==s)f[m][m]=-1;
    cout<<f[m][m]<<endl;
    return 0;
}
