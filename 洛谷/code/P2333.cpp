// https://www.luogu.com.cn/problem/P2333
#include<bits/stdc++.h>
using namespace std;
#define ld long double
const ld eps = 1e-8;
const ld PI = acos(-1);

int n;
struct Point{
    ld x,y;
};
Point p[51];
ld area;
ld r;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}


Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

ld dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

ld len(Point a){
    return sqrtl(dot(a,a));
}

ld operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

ld sector(Point a,Point b){
    ld angle=acos((dot(a,b)/len(a)/len(b)));
    if(a*b<0){
        angle=-angle;
    }
    return r*r*angle/2;
}

Point rorate(Point a,double b){
    return {a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b)};
}

Point operator/(Point a,ld b){
    return {a.x/b,a.y/b};
}

Point operator*(Point a,ld b){
    return {a.x*b,a.y*b};
}

Point norm(Point a){
    return a/len(a);
}

Point getNode(Point a,Point u,Point b,Point v){
    ld t=(a-b)*v/(v*u);
    return a+u*t;
}

bool onSegment(Point p,Point a,Point b){
    return fabs((a-p)*(b-p))<eps&& (dot(a-p,b-p)<=0);
}

ld getDP2(Point a,Point b,Point &pa,Point &pb){
    Point o={0,0};
    Point e=getNode(a,b-a,o,rorate(b-a,PI/2));
    ld d=len(e);
    if(!onSegment(e,a,b)){
        d=min(len(a),len(b));
    }
    if(r<=d){
        return d;
    }
    ld length=sqrt(r*r-len(e)*len(e));
    pa=e+norm(a-b)*length;
    pb=e+norm(b-a)*length;
    return d;
}

ld getArea(Point a,Point b){
    if(fabs(a*b)<eps){
        return 0;
    }
    ld da=len(a),db=len(b);
    if(r>=da&&r>=db){
        return a*b/2;
    }

    Point pa,pb;
    ld d=getDP2(a,b,pa,pb);
    if(r<=d){
        return sector(a,b);
    }
    if(r>=da){
        return a*pb/2+sector(pb,b);
    }
    if(r>=db){
        return sector(a,pa)+pa*b/2;
    }
    return sector(a,pa)+pa*pb/2+sector(pb,b);
}

bool check(ld limit){
    r=limit;
    ld sum=0;
    for(int i=1;i<=n;i++){
        sum+=getArea(p[i],p[i%n+1]);
    }
    if(sum<0){
        sum=-sum;
    }
    return sum+eps>=area;
}

int main()
{
    cin>>n>>area;
    ld l=0,r=0;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        ld d=len(p[i]);
        r=max(r,d);
    }
    ld ans=r;
    while(l+eps<r){
        ld mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-eps;
        }
        else{
            l=mid+eps;
        }
    }
    cout<<fixed<<setprecision(2)<<ans<<endl;
    return 0;
}