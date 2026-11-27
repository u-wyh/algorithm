// https://www.luogu.com.cn/problem/P4703
// 题意：在边长 l 的正方形 [0, l]^2 内有 n 个半径为 l/n 的信号屏蔽器
// 求正方形内任一不被任何屏蔽器覆盖的点（距各圆心 >= l/n + 10^-6），无解输出 GG。
// 数据范围：1 <= n <= 10，1 <= l <= 10^5，0 <= x_i, y_i <= l。
#include<bits/stdc++.h>
// 算法标签：枚举、计算几何
using namespace std;
const double eps = 1e-5;

int n;
double l;
struct Point{
    double x,y;
};
struct Circle{
    Point c;
    double r;
};
Circle circle[11];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double dis(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

bool check(Point p){
    for(int i=1;i<=n;i++){
        if(dis(p-circle[i].c)<circle[i].r+eps){
            return false;
        }
    }
    return true;
}

int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++){
        cin>>circle[i].c.x>>circle[i].c.y;
        circle[i].r=l/n;
    }
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n+1;j++){
            double x=1.0*(i-1)/n*l;
            double y=1.0*(j-1)/n*l;
            if(check({x,y})){
                cout<<fixed<<setprecision(3)<<x<<' '<<y<<endl;
                return 0;
            }
        }
    }
    cout<<"GG";
    return 0;
}