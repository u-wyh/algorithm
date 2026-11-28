// https://www.luogu.com.cn/problem/P1514
// 题意：给 N 行 M 列城市的海拔。
// 第 1 行可建水厂，水可沿上下左右相邻且海拔严格下降的路线传递。
// 若能让最后一行的全部城市得到水，输出 1 和最少水厂数；
// 否则输出 0 和最后一行不可能得到水的城市数。
// 数据范围：满分测试中 N,M 均不超过 500，海拔为正整数。
// 难度评分：1700（洛谷分级换算）
// 算法标签：深度优先搜索、贪心

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int high[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n,m;
int l[MAXN][MAXN],r[MAXN][MAXN];

void dfs(int x,int y){
    vis[x][y]=true;
    for(int i=0;i<4;i++){
        int nx=x+walk[i][0];
        int ny=y+walk[i][1];
        if(nx<1||nx>n||ny<1||ny>m){
            continue;
        }
        if (high[nx][ny]>=high[x][y])
            continue;
        if(!vis[nx][ny]){
            dfs(nx,ny);
        }
        l[x][y]=min(l[x][y],l[nx][ny]);
        r[x][y]=max(r[x][y],r[nx][ny]);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>high[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            l[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=m;i++){
        l[n][i]=r[n][i]=i;
    }
    for(int i=1;i<=m;i++){
        if(!vis[1][i]){
            dfs(1,i);
        }
    }
    int cnt=0;
    for(int i=1;i<=m;i++){
        if(!vis[n][i]){
            cnt++;
        }
    }
    if(cnt){
        cout<<0<<endl<<cnt<<endl;
        return 0;
    }
    int left=1,right=0;
    while(left<=m){
        for(int i=1;i<=m;i++){
            if(l[1][i]<=left){
                right=max(right,r[1][i]);
            }
        }
        cnt++;
        left=right+1;
    }
    cout<<1<<endl<<cnt<<endl;
    return 0;
}
