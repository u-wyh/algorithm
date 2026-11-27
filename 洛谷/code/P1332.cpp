// https://www.luogu.com.cn/problem/P1332
// 题意：给 n×m 的网格和 a 个初始标记点。每小时标记会向上下左右相邻格扩展一层。给 b 个查询坐标，按顺序输出每个格子首次被标记的时刻，源点为 0。
// 数据范围：1 ≤ n,m ≤ 500，1 ≤ a,b ≤ 10^5。
// 算法标签：广度优先搜索

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 501;
const int MAXM = 501;

int n,m,a,b;
struct coord{
    int x,y;
};
queue<coord>q;
int ans[MAXN][MAXN];;
coord t[100005];
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
    cin>>n>>m>>a>>b;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans[i][j]=-1;
        }
    }
    for(int i=1;i<=a;i++){
        int x,y;
        cin>>x>>y;
        q.push({x,y});
        ans[x][y]=0;
    }
    for(int i=1;i<=b;i++){
        cin>>t[i].x>>t[i].y;
    }
    while(!q.empty()){
        coord u=q.front();
        int ux=u.x,uy=u.y;
        q.pop();
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            int d=ans[ux][uy];
            if(x<=0||x>n||y<=0||y>m||ans[x][y]!=-1)
                continue;
            ans[x][y]=d+1;
            q.push({x,y});
        }
    }
    for(int i=1;i<=b;i++){
        cout<<ans[t[i].x][t[i].y]<<endl;
    }
    return 0;
}
