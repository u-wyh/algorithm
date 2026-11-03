// https://codeforces.com/problemset/problem/600/D
#include<bits/stdc++.h>
using namespace std;

const long double PI=acosl(-1.0L);

struct Point{
    long double x,y;

    Point operator-(Point b) const{
        return {x-b.x,y-b.y};
    }
};

Point a,b;
long double r1,r2;

long double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

long double len(Point a){
    return sqrtl(dot(a,a));
}

long double getAngle(long double x){
    // 防止浮点误差使acos参数超出[-1,1]
    if(x>1) x=1;
    if(x<-1) x=-1;
    return acosl(x);
}

int main(){
    cin>>a.x>>a.y>>r1;
    cin>>b.x>>b.y>>r2;

    // 计算圆心距
    long double d=len(b-a);

    long double ans=0;

    if(d>=r1+r2){
        // 相离或者外切
        ans=0;
    }
    else if(d+r1<=r2){
        // 第一个圆被第二个圆包含
        ans=PI*r1*r1;
    }
    else if(d+r2<=r1){
        // 第二个圆被第一个圆包含
        ans=PI*r2*r2;
    }
    else{
        // 余弦定理求圆心到公共弦的有向距离
        long double x=(r1*r1+d*d-r2*r2)/(2*d);

        // 勾股定理求公共弦的一半
        long double h2=r1*r1-x*x;
        if(h2<0) h2=0;
        long double h=sqrtl(h2);

        // 两个扇形对应的半圆心角
        long double alpha=getAngle(x/r1);
        long double beta=getAngle((d-x)/r2);

        // 两个扇形减去两个三角形
        ans=r1*r1*alpha+r2*r2*beta-d*h;
    }

    cout<<fixed<<setprecision(15)<<ans<<endl;

    return 0;
}