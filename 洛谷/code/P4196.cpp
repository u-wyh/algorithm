// https://www.luogu.com.cn/problem/P4196
// 题意：逆时针给出 n 个凸多边形的顶点坐标，求它们交集部分的面积（保留 3 位小数）。
// 数据范围：2 <= n <= 10，3 <= m_i <= 50，每维坐标为 [-1000, 1000] 内的整数。
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-9;

int n,m;
struct Point{
    double x,y;
};
Point p[55];
struct Line{
    Point s,e;
};
int lcnt;
Line l[505];
Line q[505];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point operator/(Point a,double k){
    return {a.x/k,a.y/k};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double angle(Line a){
    return atan2(a.e.y-a.s.y,a.e.x-a.s.x);
}

bool cmp(Line a,Line b){
    double A=angle(a),B=angle(b);
    return fabs(A-B)>eps?A<B:(a.e-a.s)*(b.e-a.s)<0;
}

Point cross(Line a,Line b){
    Point u=a.s-b.s,v=a.e-a.s,w=b.e-b.s;
    double t=u*w/(w*v);
    return a.s+v*t;
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool right(Line a,Line b,Line c){
    Point p=cross(b,c);
    return (a.e-a.s)*(p-a.s)<0;
}

double half_plane(){
    sort(l+1,l+lcnt+1,cmp);
    int h=1,t=1;
    q[1]=l[1];
    for(int i=2;i<=lcnt;i++){
        if(angle(l[i])-angle(l[i-1])<eps){
            continue;
        }
        while(h<t && right(l[i],q[t],q[t-1])){
            t--;
        }
        while(h<t && right(l[i],q[h],q[h+1])){
            h++;
        }
        q[++t]=l[i];
    }
    while(h<t && right(q[h],q[t],q[t-1])){
        t--;
    }

    int cnt=0;
    for(int i=h;i<t;i++){
        p[++cnt]=cross(q[i],q[i+1]);
    }
    p[++cnt]=cross(q[t],q[h]);
    double sum=0;
    for(int i=2;i<cnt;i++){
        sum+=cross(p[1]-p[i],p[1]-p[i+1]);
    }
    return sum/2;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m;
        for(int j=1;j<=m;j++){
            cin>>p[j].x>>p[j].y;
        }
        for(int j=1;j<=m;j++){
            l[++lcnt]={p[j],p[j%m+1]};
        }
    }
    cout<<fixed<<setprecision(3)<<half_plane()<<endl;
    return 0;
}