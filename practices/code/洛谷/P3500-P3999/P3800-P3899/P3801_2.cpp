// https://www.luogu.com.cn/problem/P3801
// 题意：第一行输入矩阵大小 n, m 和操作数 q，初始 n*m 网格全无红雾。
// 接下来 q 行操作：
// 1 x y 表示在 (x, y)
// 向四个方向释放无限长红雾
// （影响整行与整列但不影响 (x, y) 本身，两阵红雾碰撞则消失
// 即对应格状态翻转）；
// 2 x1 y1 x2 y2 查询左上角 (x1, y1) 到右下角
// (x2, y2) 的矩形内被红雾遮盖的格子数。
// 对每个操作 2 输出一行一个整数。
// 数据范围：对于 100% 的数据，1 <= n, m, q <= 10^5，
// 1 <= x1 <= x2 <= n，1 <= y1 <= y2 <= m
// 1 <= x <= n，1 <= y <= m。
// 难度评分：1700（洛谷分级换算）
// 算法标签：树状数组、容斥原理
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
int n,m,q;
int dx[MAXN],dy[MAXN];//两个树状数组
int ax[MAXN],ay[MAXN];//单点的存放（方便修改）
int lowbit(int x)
{
    return x&(x^(x-1));
}
void gai(int *c,int x,int y)//单点修改
{
    while(x <= *c)
    {
        *(c+x) += y;
        x += lowbit(x);
    }
}
int qiu(int *c,int x)//区间求值
{
    int ans = 0;
    while(x >= 1)
    {
        ans += *(c+x);
        x -= lowbit(x);
    }
    return ans;
}
void huan(int x,int y)
{
    if(ax[x] == 1)
    {
        ax[x] = 0;
        gai(dx,x,-1);
    }
    else
    {
        ax[x] = 1;
        gai(dx,x,1);
    }
    if(ay[y] == 1)
    {
        ay[y] = 0;
        gai(dy,y,-1);
    }
    else
    {
        ay[y] = 1;
        gai(dy,y,1);
    }
}
long long suan(int x1,int y1,int x2,int y2)//计算有红雾的地方
{
    int s1 = qiu(dx,x2) - qiu(dx,x1 - 1);
    int s2 = qiu(dy,y2) - qiu(dy,y1 - 1);
    long long ans = (long long)s1*(y2-y1+1) + (long long)s2*(x2-x1+1) - s1*s2*2;
    return ans;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    int cmd,x,y,x2,y2;
    dx[0] = n;
    dy[0] = m;
    for(int i = 1; i <= q; i ++)
    {
        scanf("%d",&cmd);
        if(cmd == 1)
        {
            scanf("%d%d",&x,&y);
            huan(x,y);
        }
        else
        {
            scanf("%d%d%d%d",&x,&y,&x2,&y2);
            cout<<suan(x,y,x2,y2)<<endl;
        }
    }
    return 0;
 }
