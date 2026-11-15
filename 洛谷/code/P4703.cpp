// https://www.luogu.com.cn/problem/P4703
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-5;

int n;
double l;
struct Point{
    double x,y;
};
struct Circle{
    Point c;
    double r;
};
Circle circle[11];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double dis(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

bool check(Point p){
    for(int i=1;i<=n;i++){
        if(dis(p-circle[i].c)<circle[i].r+eps){
            return false;
        }
    }
    return true;
}

int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++){
        cin>>circle[i].c.x>>circle[i].c.y;
        circle[i].r=l/n;
    }
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n+1;j++){
            double x=1.0*(i-1)/n*l;
            double y=1.0*(j-1)/n*l;
            if(check({x,y})){
                cout<<fixed<<setprecision(3)<<x<<' '<<y<<endl;
                return 0;
            }
        }
    }
    cout<<"GG";
    return 0;
}