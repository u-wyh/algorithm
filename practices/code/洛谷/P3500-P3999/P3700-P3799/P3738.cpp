// https://www.luogu.com.cn/problem/P3738
// 题意：输入多边形顶点数 n、按逆时针顺序给出的 n 个顶点坐标
// (x_i, y_i)，以及侦察员初始位置 (X, Y)。
// 侦察员沿垂直于 X
// 轴方向从南向北（即沿直线 x = X 从 Y 向 +∞）穿越该封闭多边形
// （不一定凸）。
// 输出侦察员行走路线在敌占区（多边形）内部的总长度的整数部分。
// 数据范围：3 <= n <= 50，0 <= x_i, y_i <= 1000，
// 0 <= X <= 1000，-100 <= Y < 0。
// 难度评分：1900（洛谷分级换算）
// 算法标签：计算几何、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];
Point u;
Point nums[MAXN];

bool cmp(Point a,Point b){
    return a.y<b.y;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    p[n+1]=p[1];
    cin>>u.x>>u.y;
    int cnt=0;
    for(int i=1;i<=n;i++){
        Point a=p[i];
        Point b=p[i+1];
        if(a.x<b.x){
            swap(a,b);
        }
        
        if((a.x<=u.x && u.x<b.x) ||  (b.x<=u.x && u.x<a.x)){
            nums[++cnt]={u.x, (u.x-a.x)/(b.x-a.x)*(b.y-a.y)+a.y};
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    double ans=0;
    for(int i=1;i<=cnt;i+=2){
        ans+=nums[i+1].y-nums[i].y;
    }
    cout<<(int )ans<<endl;
    return 0;
}