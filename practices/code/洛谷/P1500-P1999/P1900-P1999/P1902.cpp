// https://www.luogu.com.cn/problem/P1902
// 题意：给定 n 行 m 列的网格及各格代价。
// 从首行任意格出发，上下左右移动，要求末行每个格子都能从首行到达。
// 求能满足这一条件的最小格子代价上限。
// 数据范围：n,m ≤ 1000，格子代价 ≤ 1000，首末行代价均为 0。
// 难度评分：1300（洛谷分级换算）
// 算法标签：二分答案、广度优先搜索

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

struct node{
    int x,y;
    int goal;
};
int nums[MAXN][MAXN];
int l,r,ans=0;
int n,m;
queue<node>q;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
bool vis[MAXN][MAXN];

void clean(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            vis[i][j]=false;
        }
    }
    while(!q.empty()){
        q.pop();
    }
}

bool bfs(int limit){
    for(int i=1;i<=m;i++){
        vis[1][i]=true;
        q.push({1,i,0});
    }
    while(!q.empty()){
        node u=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            if(vis[x][y]||x>n||y>m||x==0||y==0||nums[x][y]>limit){
                continue;
            }
            int goal=max(u.goal,nums[x][y]);
            if(x==n&&goal==limit)
                return 1;
            vis[x][y]=true;
            q.push({x,y,goal});
        }
    }
    return 0;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            r=max(nums[i][j],r);
        }
    }
    while(l<=r){
        clean();
        int mid=(l+r)>>1;
        if(bfs(mid)){
            r=mid-1;
            ans=mid;
        }else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
