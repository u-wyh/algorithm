// https://www.luogu.com.cn/problem/P4576
// 题意：n*n 棋盘上白子先走每次四方向走 1 格，黑子后走每次四方向走 1 或 2 格，走到对方所在格即吃子获胜，双方绝顶聪明（赢者求快、输者拖延）
// 判胜负并求总步数（无必胜输出 DRAW）。
// 数据范围：2 <= n <= 20。
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int dp[2][65][21][21][21][21];
int n;

int dfs(int u,int now,int x1,int y1,int x2,int y2){
    if(now>3*n){
        return INF;
    }
    if(dp[u][now][x1][y1][x2][y2]){
        return dp[u][now][x1][y1][x2][y2];
    }
    if(x1==x2&&y1==y2){
        return u?INF:0;
    }
    int ans;
    if(u==0){
        ans=0;
        if(x1>1) ans=max(ans,dfs(1,now+1,x1-1,y1,x2,y2));
        if(x1<n) ans=max(ans,dfs(1,now+1,x1+1,y1,x2,y2));
        if(y1>1) ans=max(ans,dfs(1,now+1,x1,y1-1,x2,y2));
        if(y1<n) ans=max(ans,dfs(1,now+1,x1,y1+1,x2,y2));
    }
    else{
        ans=INF;
        if(x2>1) ans=min(ans,dfs(0,now+1,x1,y1,x2-1,y2));
        if(x2>2) ans=min(ans,dfs(0,now+1,x1,y1,x2-2,y2));
        if(x2<n) ans=min(ans,dfs(0,now+1,x1,y1,x2+1,y2));
        if(x2<n-1) ans=min(ans,dfs(0,now+1,x1,y1,x2+2,y2));
        if(y2>1) ans=min(ans,dfs(0,now+1,x1,y1,x2,y2-1));
        if(y2>2) ans=min(ans,dfs(0,now+1,x1,y1,x2,y2-2));
        if(y2<n) ans=min(ans,dfs(0,now+1,x1,y1,x2,y2+1));
        if(y2<n-1) ans=min(ans,dfs(0,now+1,x1,y1,x2,y2+2));
    }
    dp[u][now][x1][y1][x2][y2]=++ans;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int x1,x2,y1,y2;
    cin>>n>>x1>>y1>>x2>>y2;
    if(abs(x1-x2)+abs(y1-y2)<=1){
        cout<<"WHITE 1"<<endl;
        return 0;
    }
    cout<<"BLACK "<<dfs(0,0,x1,y1,x2,y2)<<endl;
    return 0;
}
