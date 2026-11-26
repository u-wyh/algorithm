// https://www.luogu.com.cn/problem/P2013
// 题意：给定 N 座灯塔的名称和坐标，再给船的航向以及两座灯塔相对于航向的方位角。
// 角度从正北或当前航向顺时针量起。
// 求船的坐标，保留两位小数，无法确定时输出 NO ANSWER。
// 数据范围：1 ≤ N ≤ 30，灯塔名由不超过 20 个字母组成。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 35;
const double PI = acos(-1);
const double eps = 1e-9;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];
map<string,int>mp;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point getdir(double angle){
    double rad=angle*PI/180;
    return {sin(rad),cos(rad)};
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s>>p[i].x>>p[i].y;
        mp[s]=i;
    }

    double angle;
    cin>>angle;

    string s1,s2;
    double a1,a2;
    cin>>s1>>a1;
    cin>>s2>>a2;

    Point A=p[mp[s1]];
    Point B=p[mp[s2]];

    Point u=getdir(angle+a1+180);
    Point v=getdir(angle+a2+180);

    double d=u*v;
    if(abs(d)<eps){
        cout<<"NO ANSWER\n";
        return 0;
    }

    double t=((B-A)*v)/d;
    double s=((B-A)*u)/d;

    if(t<-eps || s<-eps){
        cout<<"NO ANSWER\n";
        return 0;
    }

    Point ans=A+u*t;
    cout<<fixed<<setprecision(2)<<ans.x<<" "<<ans.y<<"\n";

    return 0;
}
