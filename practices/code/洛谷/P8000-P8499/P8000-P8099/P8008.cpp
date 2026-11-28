// https://www.luogu.com.cn/problem/P8008
// 题意：平面上有无限多根平行直线（竹子）
// 分别过点 (k * a, 0)（k ∈ Z）
// 且与 x 轴正方向逆时针夹角为 θ 度（如图 7j0tx5xy.png 所示）。
// 给定一个按顺时针顺序给出 n 个顶点的简单多边形（保证无任何边与竹子平行），
// 求落在多边形内部的竹子线段总长度。
// 第一行输入 n，接下来 n 行每行坐标 (x_i, y_i)，
// 接着输入实数 θ 和 a（输入浮点数均保留 4 位小数）。
// 输出一行一个实数，
// 满足 |ans - std| / max(1.0, std)
// <= 10^{-6}（Special Judge）。
// 数据范围：3 <= n <= 10^5，
// |x_i|, |y_i| <= 10^4，θ ∈ [1, 179)，
// a ∈ [0.1, 100]。
// 难度评分：1600（洛谷分级换算）
// 算法标签：计算几何、数学
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const long double PI = acosl(-1);
const long double eps = 1e-11L;

int n;
long double theta,a,d;

struct Point{
    long double x,y;
};
Point p[MAXN];

Point rorate(Point p,long double c,long double s){
    return {p.x*c+p.y*s,-p.x*s+p.y*c};
}

long double compute(Point u,Point v){
    int sign=1;
    if(u.y<v.y){
        sign=-1;
        swap(u,v);
    }
    long long l=ceill(v.y/d);
    long long r=ceill(u.y/d)-1;
    if(l>r){
        return 0;
    }
    long long cnt=r-l+1;
    long double mid=(l+r)/2.0*d;
    long double x=v.x+(u.x-v.x)*(mid-v.y)/(u.y-v.y);;
    return sign*cnt*x;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    cin>>theta>>a;
    theta=theta*PI/180;
    long double s=sinl(theta);
    long double c=cosl(theta);
    d=a*s;

    for(int i=1;i<=n;i++){
        p[i]=rorate(p[i],c,s);
    }
    p[n+1]=p[1];

    long double ans=0;
    for(int i=1;i<=n;i++){
        long double val=compute(p[i],p[i+1]);
        ans=ans+val;
    }
    cout<<fixed<<setprecision(12)<<ans<<endl;
    return 0;
}