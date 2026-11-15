// https://www.luogu.com.cn/problem/P12144
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const long double PI = acos(-1);

int n;
struct Point{
    long double x,y;
};
struct Circle{
    Point p;
    long double r;
};
Circle circle[MAXN];
struct Angle{
    long double l,r;
};
Angle angle[MAXN];

bool cmp(Angle a,Angle b){
    return a.l<b.l;
}

long double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

void compute(){
    for(int i=1;i<=n;i++){
        long double theta=asin(circle[i].r/len(circle[i].p));
        long double theta1=atan(circle[i].p.y/circle[i].p.x);
        angle[i].l=theta1-theta;
        angle[i].r=theta1+theta;
    }
    // angle[n+1]={0,0};
    // angle[n+2]={PI/2,PI/2};
    // sort(angle+1,angle+n+3,cmp);
    sort(angle+1,angle+n+1,cmp);
    long double res=0;
    long double r=angle[1].r;
    for(int i=2;i<=n;i++){
        if(angle[i].l>r){
            res+=angle[i].l-r;
            r=max(r,angle[i].r);
        }
        else{
            r=max(r,angle[i].r);
        }
    }
    res+=angle[1].l;
    res+=PI/2-r;
    cout<<fixed<<setprecision(3)<<(res*2/PI)<<endl;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>circle[i].p.x>>circle[i].p.y>>circle[i].r;
    }
    compute();
    return 0;
}