// https://www.luogu.com.cn/problem/P1562
// 题意：输入 N 及 N*N 棋盘，* 表示可放皇后，. 表示不可放。
// 放置 N 个皇后，使每行、每列恰有 1 个，每条对角线至多 1 个。
// 输出合法放置方案的总数。
// 数据范围：
// 0 < N <= 14（棋盘大小）
// 算法标签：深度优先搜索、回溯
#include<bits/stdc++.h>
using namespace std;

int n;
char s[15][15];
int nums[15][15],b1[15],b2[30],b3[30];
int ans;

void dfs(int x){
    if(x>n){
        ans++;
        return ;
    }
    for(int i=1;i<=n;i++){
        if(b1[i]==0&&b2[x+i]==0&&b3[x-i+15]==0&&nums[x][i]==1){
            b1[i]=1,b2[x+i]=1,b3[x-i+15]=1;
            dfs(x+1);
            b1[i]=0,b2[x+i]=0,b3[x-i+15]=0;
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>s[i][j];
            if(s[i][j]=='*'){
                nums[i][j]=1;
            }
        }
    }
    dfs(1);
    printf("%d\n",ans);
    return 0;
}
