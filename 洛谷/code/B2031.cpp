// https://www.luogu.com.cn/problem/B2031
#include<bits/stdc++.h>
using namespace std;

struct Point{
    double x,y;
};
Point a,b,c;
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
double cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y;
    double ans=cross(a,b,c);
    ans=fabs(ans);
    ans/=2;
    cout<<fixed<<setprecision(2);
    cout<<ans<<endl;
    return 0;
}