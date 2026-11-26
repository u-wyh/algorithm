// https://www.luogu.com.cn/problem/P3956
// 题意：m * m 棋盘中有 n 个格子有颜色（0 红或 1 黄），其余无色，保证 (1, 1) 有色。
// 从 (1, 1) 走到 (m, m)，每次上下左右移动：
// 相邻两格同色花费 0 金币，异色花费 1 金币；
// 也可花 2 金币施展魔法把下一个无色格子临时变为指定颜色，但不能连续对无色格子使用魔法（离开临时变色格后它恢复无色）。
// 求到达 (m, m) 的最少金币数，不可达输出 -1。
// 数据范围：1 <= m <= 100，1 <= n <= 10^3，0 <= c <= 1。
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
