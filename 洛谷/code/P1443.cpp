// https://www.luogu.com.cn/problem/P1443
// 题意：棋盘有 n 行 m 列，马从 (x,y) 出发，每步按象棋马的跳法移动。对每个格子输出最少步数，跳不到的格子输出 -1。
// 数据范围：1 ≤ x ≤ n ≤ 400，1 ≤ y ≤ m ≤ 400。
// 算法标签：广度优先搜索

#include<bits/stdc++.h>

using namespace std;

#define MAXN 310

struct coord{
    int x,y;
};
queue<coord>Q;
int ans[MAXN][MAXN];
int walk[8][2]={{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};

int main()
{
    int n,m,sx,sy;
    memset(ans,-1,sizeof(ans));
    cin>>n>>m>>sx>>sy;
    coord tmp={sx,sy};
    Q.push(tmp);
    ans[sx][sy]=0;
    while(!Q.empty()){
        coord u=Q.front();
        int ux=u.x,uy=u.y;
        Q.pop();
        for(int k=0;k<8;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            int d=ans[ux][uy];
            if(x<1||x>n||y<1||y>m||ans[x][y]!=-1)
                continue;
            ans[x][y]=d+1;
            coord tmp={x,y};
            Q.push(tmp);
        }
    }
    for(int i=1;i<=n;i++,puts(" "))
        for(int j=1;j<=m;j++)
            printf("%-5d",ans[i][j]);
    return 0;
}
