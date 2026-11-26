// https://www.luogu.com.cn/problem/P1183
// 题意：给定一个边均平行于坐标轴的简单多边形，按逆时针给出各顶点坐标。
// 题意：可能存在连续三个顶点共线，最后一条边由末点连回首点。
// 输入：第一行输入顶点数 n，接下来 n 行每行输入顶点坐标 x, y。
// 输出：一行输出一个整数，表示多边形的面积。
// 数据范围：1 <= n <= 100。
// 数据范围：-200 <= x, y <= 200。
#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
};
int n;
Point nums[205];
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
int operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
int cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    int ans=0;
    for(int i=2;i<=n-1;i++){
        ans+=cross(nums[1],nums[i],nums[i+1]);
    }
    ans/=2;
    ans=abs(ans);
    cout<<ans<<endl;
    return 0;
}