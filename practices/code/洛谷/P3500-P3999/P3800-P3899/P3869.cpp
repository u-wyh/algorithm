// https://www.luogu.com.cn/problem/P3869
// 题意：第一行输入迷宫行列数 r, c，
// 接下来 r 行输入迷宫（. 通路、# 墙、S 起点、T 宝藏）
// 再输入机关数 k 及 k 行机关描述 r_i, c_i, R_i, C_i。
// 每当走到 (r_i, c_i) 时，
// 格子 (R_i, C_i) 的通行状态会翻转（. 与 # 互换）；
// 每次可向四连通格子走一步，不可越界，S 与 T 不受机关影响。
// 输出从起点到达宝藏的最少步数（保证有解）。
// 数据范围：对于全部数据，5 <= r, c <= 30，
// 0 <= k <= 10，1 <= r_i, R_i <= r
// 1 <= c_i, C_i <= c。
// 难度评分：1400（洛谷分级换算）
// 算法标签：广度优先搜索、状态压缩
#include<bits/stdc++.h>
using namespace std;

int n,m,t;
int sti,stj,eni,enj;
int nums[30][30];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node{
    int x,y,status;
};
int dp[30][30][1<<10];
queue<node>q;
struct change{
    int a,b,c,d;
}num[10];

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char c;
            cin>>c;
            if(c=='S'){
                sti=i;
                stj=j;
                nums[i][j]=1;
            }
            else if(c=='T'){
                eni=i;
                enj=j;
                nums[i][j]=1;
            }
            else if(c=='.'){
                nums[i][j]=1;
            }
            //cout<<nums[i][j]<<' ';
        }
        //cout<<endl;
    }
    //cout<<sti<<' '<<stj<<' '<<eni<<' '<<enj<<endl;
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>num[i].a>>num[i].b>>num[i].c>>num[i].d;
        num[i].a-=1;
        num[i].b-=1;
        num[i].c-=1;
        num[i].d-=1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<(1<<t);k++){
                dp[i][j][k]=0;
            }
        }
    }
    q.push({sti,stj,0});
    dp[sti][stj][0]=1;
    while(!q.empty()){
        //cout<<666<<endl;
        node u=q.front();
        q.pop();
        if(u.x==eni&&u.y==enj){
            //cout<<777<<endl;
            cout<<dp[u.x][u.y][u.status]-1;
            return 0;
        }
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            int now=u.status;
            if(x>=n||x<0||y<0||y>=m){
                continue;
            }
            int flag=1;
            if(nums[x][y]==0){
                flag=0;
            }
            for(int j=0;j<t;j++){
                if(num[j].a==x&&num[j].b==y){
                    now^=(1<<j);
                }
                if(x==num[j].c&&y==num[j].d&&((u.status>>j)&1))
                    flag^=1;
            }
            if(flag&&!dp[x][y][now]){
                dp[x][y][now]=dp[u.x][u.y][u.status]+1;
                q.push({x,y,now});
            }
        }
    }
    return 0;
}
