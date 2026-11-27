// https://www.luogu.com.cn/problem/P6732
// 题意：T 组数据，
// 每组给出平面直角坐标系上两个相离正方形（未必与坐标轴平行）各 4 个顶点的坐标
// 求任意一条严格将两正方形分隔到两侧（与正方形无公共点）的直线
// ax + by = c。
// 数据范围：1 <= T <= 10000，
// 输入坐标绝对值不超过 10^3 且小数点后最多 3 位。
// 算法标签：计算几何、枚举
#include<bits/stdc++.h>
using namespace std;
const long double eps = 1e-12L;
const long double INF = 1e100L;

struct Point{
    long double x,y;
};
Point p[10];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

long double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

long double len(Point x){
    return sqrt(dot(x,x));
}

bool check(Point d){
    Point v={-d.y,d.x};
    long double length=len(v);
    v.x/=length;
    v.y/=length;
    
    long double la=INF,ra=-INF;
    long double lb=INF,rb=-INF;

    for(int i=1;i<=4;i++){
        long double x=dot(p[i],v);
        la=min(la,x);
        ra=max(ra,x);
    }

    for(int i=5;i<=8;i++){
        long double x=dot(p[i],v);
        lb=min(lb,x);
        rb=max(rb,x);
    }

    if(ra+eps<lb){
        long double c=(ra+lb)/2;
        cout<<fixed<<setprecision(15);
        cout<<v.x<<" "<<v.y<<" "<<c<<"\n";
        return true;
    }

    if(rb+eps<la){
        long double c=(rb+la)/2;
        cout<<fixed<<setprecision(15);
        cout<<v.x<<" "<<v.y<<" "<<c<<"\n";
        return true;
    }

    return false;
}

void solve(){
    for(int i=1;i<=8;i++){
        cin>>p[i].x>>p[i].y;
    }

    for(int i=1;i<=8;i++){
        for(int j=i+1;j<=8;j++){
            if((i<=4)!=(j<=4)){
                continue;
            }
            if(check(p[j]-p[i])){
                return ;
            }
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}