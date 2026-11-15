// https://www.luogu.com.cn/problem/P8008
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const long double PI = acosl(-1);
const long double eps = 1e-11L;

int n;
long double theta,a,d;

struct Point{
    long double x,y;
};
Point p[MAXN];

Point rorate(Point p,long double c,long double s){
    return {p.x*c+p.y*s,-p.x*s+p.y*c};
}

long double compute(Point u,Point v){
    int sign=1;
    if(u.y<v.y){
        sign=-1;
        swap(u,v);
    }
    long long l=ceill(v.y/d);
    long long r=ceill(u.y/d)-1;
    if(l>r){
        return 0;
    }
    long long cnt=r-l+1;
    long double mid=(l+r)/2.0*d;
    long double x=v.x+(u.x-v.x)*(mid-v.y)/(u.y-v.y);;
    return sign*cnt*x;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    cin>>theta>>a;
    theta=theta*PI/180;
    long double s=sinl(theta);
    long double c=cosl(theta);
    d=a*s;

    for(int i=1;i<=n;i++){
        p[i]=rorate(p[i],c,s);
    }
    p[n+1]=p[1];

    long double ans=0;
    for(int i=1;i<=n;i++){
        long double val=compute(p[i],p[i+1]);
        ans=ans+val;
    }
    cout<<fixed<<setprecision(12)<<ans<<endl;
    return 0;
}