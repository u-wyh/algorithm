// https://www.luogu.com.cn/problem/P1742
// 题意：给定 N 个平面点，找出覆盖所有点的最小圆，先输出半径，再输出圆心坐标。
// 数据范围：1 ≤ N ≤ 10^5，坐标绝对值 ≤ 10^4，最多两位小数，判题误差容许 10^−9。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
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
    random_shuffle(p+1,p+n+1);
    increment();
    cout<<fixed<<setprecision(12);
    cout<<C.r<<endl<<C.p.x<<' '<<C.p.y<<endl;
    return 0;
}