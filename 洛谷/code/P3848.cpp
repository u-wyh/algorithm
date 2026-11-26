// https://www.luogu.com.cn/problem/P3848
// 题意：第一行输入棋盘边长 n 和起点坐标 (x, y)，接下来 n 行每行 n 个 0/1 数字表示棋盘。
// 跳棋规则：从当前 0 格沿上下左右 4 个方向连续越过至少 1 个 1 格落入下一个 0 格，跳过的距离为越过的 1 格数加 1；
// 每个 0 格及起点至多到达/经过一次（起点不可再到达或越过）。
// 输出能跳出的最大总距离；若不能跳则输出 0。
// 数据范围：题面输入格式给出 1 <= n <= 100（题目背景说明当前随机测试数据实际为 n <= 20）。
#include<bits/stdc++.h>
using namespace std;
#define MAX 105

int n,x1,Y1,ans=0;
int nums[MAX][MAX],vis[MAX][MAX];

void dfs(int x,int y,int k){
    ans=max(ans,k);
    for(int i=1;x+i<=n;i++){
        if(vis[x+i][y]!=-1){
            if(i==1||nums[x+i][y]==1){
                break;
            }
            vis[x+i][y]=1;
            dfs(x+i,y,k+i);
            vis[x+i][y]=0;
            break;
        }
    }
    for(int i=1;x-i>=1;i++){
        if(vis[x-i][y]!=-1){
            if(i==1||vis[x-i][y]==1){
                break;
            }
            vis[x-i][y]=1;
            dfs(x-i,y,k+i);
            vis[x-i][y]=0;
            break;
        }
    }
    for(int i=1;y+i<=n;i++){
        if(vis[x][y+i]!=-1){
            if(i==1||vis[x][y+i]==1){
                break;
            }
            vis[x][y+i]=1;
            dfs(x,y+i,k+i);
            vis[x][y+i]=0;
            break;
        }
    }
    for(int i=1;y-i>=1;i++){
        if(vis[x][y-i]!=-1){
            if(i==1||vis[x][y-i]==1){
                break;
            }
            vis[x][y-i]=1;
            dfs(x,y-i,k+i);
            vis[x][y-i]=0;
            break;
        }
    }
}

int main()
{
    memset(vis,-1,sizeof(vis));
    cin>>n>>x1>>Y1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nums[i][j];
            if(nums[i][j]==0)
                vis[i][j]=0;
        }
    }
    vis[x1][Y1]=1;
    dfs(x1,Y1,0);
    printf("%d\n",ans);
    return 0;
}

