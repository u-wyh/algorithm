// https://www.luogu.com.cn/problem/P3395
// 题意：多组测试数据，第一行输入组数 T，每组输入棋盘大小 n 及 2n-2 个路障坐标 (x, y)。
// B 君从 (1, 1) 出发每秒上下左右移动一格，第 i 秒结束后第 i 个路障落地，求能否走到 (n, n)。
// 对每组数据输出 Yes 或 No。
// 数据范围：T <= 10，n <= 1000。
#include<bits/stdc++.h>
// 算法标签：广度优先搜索
using namespace std;

int n;
int death[1005][1005],t[1005][1005];
int T;
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>T;
    while(T--){
        memset(death,10000,sizeof(death));
        memset(t,10000,sizeof(t));
        cin>>n;
        int x,y;
        for(int i=1;i<=2*n-2;i++){
            cin>>x>>y;
            death[x][y]=i;
        }
        t[1][1]=0;
        Q.push({1,1});
        while(!Q.empty()){
            coord u=Q.front();
            Q.pop();
            int ux=u.x,uy=u.y;
            for(int k=0;k<4;k++){
                int x=ux+walk[k][0],y=uy+walk[k][1];
                if(x==0||x>n||y>n||y==0||t[ux][uy]+1>=death[x][y]||t[x][y]!=10000){
                    continue;
                }
                t[x][y]=t[ux][uy]+1;
                Q.push({x,y});
            }
        }
        if(t[n][n]!=10000){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
