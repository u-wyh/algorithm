// https://www.luogu.com.cn/problem/P4009
// 题意：第一行输入 N, K, A, B, C
// 接下来 N * N 的 01 矩阵表示网格交点 (i, j) 是否已有油库（起点 (1,1) 与终点 (N,N) 无油库）。
// 汽车满油可走 K 条边（初始满油），沿网格边从 (1,1) 开往 (N,N)：若 X 或 Y 坐标减小需付费用 B；
// 经过已有油库必须加满并付费 A；
// 可在交点增设油库（费用 C，不含加油费 A）。
// 输出到达终点的最小总费用。
// 数据范围：2 <= N <= 100，2 <= K <= 10，N, K, A, B, C 均为正整数。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 15;

int n,k,a,b,c;
int nums[MAXN][MAXN];
int dp[MAXN][MAXN][MAXM];
bool vis[MAXN][MAXN][MAXM];

int walk[4][3]={{0,1,0},{1,0,0},{0,-1,1},{-1,0,1}};

struct node{
    int x,y,fuel,cost;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.cost>b.cost;
    }
};
priority_queue<node,vector<node>,compare>heap;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read(),k=read(),a=read(),b=read(),c=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]=read();
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int p=0;p<=k;p++){
                dp[i][j][p]=INT_MAX;
            }
        }
    }
    dp[1][1][k]=0;
    heap.push({1,1,k,0});
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        if(vis[tmp.x][tmp.y][tmp.fuel]){
            continue;
        }
        vis[tmp.x][tmp.y][tmp.fuel]=true;
        if(tmp.x==n&&tmp.y==n){
            cout<<tmp.cost<<endl;
            return 0;
        }
        for(int i=0;i<4;i++){
            int x=tmp.x+walk[i][0];
            int y=tmp.y+walk[i][1];
            int cost=tmp.cost+walk[i][2]*b;
            int fuel=tmp.fuel-1;
            if(x<0||x>n||y<0||y>n){
                continue;
            }
            if(fuel<0){
                continue;
            }
            if(nums[x][y]==1){
                cost+=a;
                if(cost<dp[x][y][k]){
                    dp[x][y][k]=cost;
                    heap.push({x,y,k,cost});
                }
            }
            else{
                if(cost<dp[x][y][fuel]){
                    dp[x][y][fuel]=cost;
                    heap.push({x,y,fuel,cost});
                }
                cost+=a+c;
                if(cost<dp[x][y][k]){
                    dp[x][y][k]=cost;
                    heap.push({x,y,k,cost});
                }
            }
        }
    }
    return 0;
}