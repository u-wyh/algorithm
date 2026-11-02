// https://www.luogu.com.cn/problem/P15904
#include<bits/stdc++.h>
using namespace std;
#define int long long

int xl,yl,xr,yr;
struct Point{
    int x,y;
};
Point a,b;
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
int operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
int cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

bool check(Point a,Point b,Point c,Point d){
    int x1=cross(a,b,c);
    int x2=cross(a,b,d);
    int x3=cross(c,d,a);
    int x4=cross(c,d,b);

    // 跨立实验
    bool ok1=(x1*x2<=0 && x3*x4<=0);

    // 包围盒相交
    bool ok2=
        max(min(a.x,b.x),min(c.x,d.x))<=min(max(a.x,b.x),max(c.x,d.x)) &&
        max(min(a.y,b.y),min(c.y,d.y))<=min(max(a.y,b.y),max(c.y,d.y));

    return ok1&&ok2;
}

bool in(Point a){
    if(xl<=a.x&&a.x<=xr && yl<=a.y&&a.y<=yr){
        return true;
    }
    return false;
}

void solve(){
    cin>>xl>>yl>>xr>>yr;
    cin>>a.x>>a.y>>b.x>>b.y;
    Point c,d,e,f;
    c.x=xl,c.y=yl;
    d.x=xl,d.y=yr;
    e.x=xr,e.y=yr;
    f.x=xr,f.y=yl;
    if(check(a,b,c,d) || check(a,b,d,e) || check(a,b,e,f) || check(a,b,f,c)){
        cout<<"STOP"<<endl;
    }
    else if(in(a)||in(b)){
        cout<<"STOP"<<endl;
    }
    else{
        cout<<"OK"<<endl;
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}