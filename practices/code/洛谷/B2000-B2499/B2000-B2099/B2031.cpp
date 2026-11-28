// https://www.luogu.com.cn/problem/B2031
// 题意：给三角形的三个顶点坐标
// (x1, y1)、(x2, y2)、(x3, y3)，输出三角形面积，
// 保留两位小数。
// 数据范围：每个坐标的绝对值不超过 100，最多一位小数。
// 难度评分：1100（洛谷分级换算）
// 算法标签：计算几何

#include<bits/stdc++.h>
using namespace std;

struct Point{
    double x,y;
};
Point a,b,c;
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
double cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y;
    double ans=cross(a,b,c);
    ans=fabs(ans);
    ans/=2;
    cout<<fixed<<setprecision(2);
    cout<<ans<<endl;
    return 0;
}