// https://www.luogu.com.cn/problem/P3744
// 题意：输入顶点数 N，以及按顺时针顺序给出、构成严格凸多边形的 N 个顶点坐标 (x_i, y_i)。
// 将每个顶点最多移动 D 个单位距离，求能使该凸多边形不再是凸多边形的最小实数 D。
// 输出最小 D 值，绝对或相对误差不超过 10^-4。
// 数据范围：4 <= N <= 1000，-10^9 <= x_i, y_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：计算几何、枚举
using namespace std;
const int MAXN = 1e3+5;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    p[n+1]=p[1];
    p[n+2]=p[2];

    double ans=2e9;
    for(int i=1;i<=n;i++){
        double area=abs(cross(p[i+1]-p[i],p[i+2]-p[i]));
        double h1=area/len(p[i+1]-p[i]);
        double h2=area/len(p[i+1]-p[i+2]);
        double h3=area/len(p[i+2]-p[i]);
        ans=min(ans,min({h1,h2,h3})/2);
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
    return 0;
}