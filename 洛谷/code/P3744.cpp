// https://www.luogu.com.cn/problem/P3744
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
struct Point{
    double x,y;
};
Point p[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    p[n+1]=p[1];
    p[n+2]=p[2];

    double ans=2e9;
    for(int i=1;i<=n;i++){
        double area=abs(cross(p[i+1]-p[i],p[i+2]-p[i]));
        double h1=area/len(p[i+1]-p[i]);
        double h2=area/len(p[i+1]-p[i+2]);
        double h3=area/len(p[i+2]-p[i]);
        ans=min(ans,min({h1,h2,h3})/2);
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
    return 0;
}