// https://atcoder.jp/contests/past16-open/tasks/past202309_m
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