// https://www.luogu.com.cn/problem/P4288
// 题意：平面上有 n 个用户点，增幅仪能把圆沿逆时针旋转 a 度的方向拉长 p 倍成椭圆（保持半短轴方向不变）
// 求能覆盖所有点的最小椭圆半短轴长度（保留 3 位小数）。
// 数据范围：n <= 50000，0 <= a < 180，1 <= p <= 100，|x|, |y| <= 2e8。
#include<bits/stdc++.h>
// 算法标签：最小圆覆盖、随机增量法、计算几何
using namespace std;
const int MAXN = 5e4+5;
const double PI = acos(-1);

int n;
struct Point{
    double x,y;
};
Point p[MAXN];
struct Circle{
    Point p;
    double r;
};
Circle C;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator/(Point a,double k){
    return {a.x/k,a.y/k};
}

double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

double dis(Point a,Point b){
    return len(a-b);
}

Circle cover(Point a,Point b){
    return {(a+b)/2,dis(a,b)/2};
}

Point rorate(Point a,double b){
    return {a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b)};
}

pair<Point,Point> midperp(Point a,Point b){
    return {(a+b)/2,rorate(b-a,PI/2)};
}

Point cross(Point a,Point u,Point b,Point v){
    double t=(a-b)*v/(v*u);
    return a+u*t;
}

Circle cover(Point a,Point b,Point c){
    auto u=midperp(a,b),v=midperp(a,c);
    Point p=cross(u.first,u.second,v.first,v.second);
    return {p,dis(p,a)};
}

void increment(){
    C={p[1],0};
    for(int i=2;i<=n;i++){
        if(C.r<dis(C.p,p[i])){
            C={p[i],0};
            for(int j=1;j<i;j++){
                if(C.r<dis(C.p,p[j])){
                    C=cover(p[i],p[j]);
                    for(int k=1;k<j;k++){
                        if(C.r<dis(C.p,p[k])){
                            C=cover(p[i],p[j],p[k]);
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    int a,b;
    cin>>a>>b;
    for(int i=1;i<=n;i++){
        p[i]=rorate(p[i],-1.0*a/180*PI);
        p[i].x/=b;
    }
    random_shuffle(p+1,p+n+1);
    increment();
    cout<<fixed<<setprecision(3);
    cout<<C.r<<endl;
    return 0;
}