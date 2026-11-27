// https://atcoder.jp/contests/past16-open/tasks/past202309_m
// 题意：平面上给定两条线段 AB 和 CD 的端点坐标。
// 输出：两线段相交（含端点相交）输出 Yes，否则输出 No。
// 数据范围：坐标为 [-1000, 1000] 内的整数。
// 同一条线段的两个端点不同。
// 算法标签：计算几何
#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
};

Point a,b,c,d;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

long long operator*(Point a,Point b){
    return 1LL*a.x*b.y-1LL*a.y*b.x;
}

long long cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main(){
    cin>>a.x>>a.y>>b.x>>b.y;
    cin>>c.x>>c.y>>d.x>>d.y;

    long long x1=cross(a,b,c);
    long long x2=cross(a,b,d);
    long long x3=cross(c,d,a);
    long long x4=cross(c,d,b);

    // 跨立实验
    bool ok1=(x1*x2<=0 && x3*x4<=0);

    // 包围盒相交
    bool ok2=
        max(min(a.x,b.x),min(c.x,d.x))<=min(max(a.x,b.x),max(c.x,d.x)) &&
        max(min(a.y,b.y),min(c.y,d.y))<=min(max(a.y,b.y),max(c.y,d.y));

    if(ok1 && ok2){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }

    return 0;
}