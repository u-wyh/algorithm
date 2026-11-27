// https://www.luogu.com.cn/problem/P8718
// 题意：第一行输入 x_A, y_A, x_B, y_B, L
// 第二行输入三角形三个顶点坐标 (x_1, y_1), (x_2, y_2), (x_3, y_3)；
// 求三角形与满足到 (x_A, y_A) 和 (x_B, y_B) 距离之和 <= L 的区域（椭圆）相交的面积
// 四舍五入保留 2 位小数输出（误差不超过 0.01 即得分）。
// 数据范围：(x_A, y_A) != (x_B, y_B)，所有坐标在 [-1000, 1000] 内，0 < L <= 1000。
// 算法标签：计算几何
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
const double PI = acos(-1);

struct Point{
    double x,y;
};
Point p[5];
Point A,B;
double L;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator/(Point a,double k){
    return {a.x/k,a.y/k};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double sector(double r,double t){
    return r*r*t/2;
}

double sector(Point a,Point b,double r){
    return sector(r,atan2(cross(a,b),dot(a,b)));
}

double sector(Point a,Point b){
    return sector(a,b,1);
}

double getDP2(Point a,Point b,Point &pa,Point &pb){
    Point v=b-a;
    double t=dot(a,v)/dot(v,v);
    Point o=a-v*t;
    double d=len(o);
    double k=sqrt(1-d*d);
    v=v/len(v);
    pa=o-v*k;
    pb=o+v*k;
    return d;
}

double getArea(Point a,Point b){
    if(fabs(cross(a,b))<eps){
        return 0;
    }
    double da=len(a);
    double db=len(b);
    double r=1;
    if(r>=da&&r>=db){
        return cross(a,b)/2;
    }
    Point pa,pb;
    double d=getDP2(a,b,pa,pb);
    if(r<=d){
        return sector(a,b);
    }
    if(r>=da){
        return cross(a,pb)/2+sector(pb,b);
    }
    if(r>=db){
        return sector(a,pa)+sector(pa,b);
    }
    return sector(a,pa)+cross(pa,pb)/2+sector(pb,b);
}

double area(){
    double res=0;
    p[4]=p[1];
    for(int i=1;i<=3;i++)
        res+=getArea(p[i],p[i+1]);
    return fabs(res);
}

int main()
{
    cin>>A.x>>A.y>>B.x>>B.y>>L;
    for(int i=1;i<=3;i++){
        cin>>p[i].x>>p[i].y;
    }
    double d=len(B-A);
    if(L<d){
        cout<<"0.00"<<endl;
        return 0;
    }
    double a=L/2;
    double b=sqrt(a*a-d*d/4);
    Point O=(A+B)/2;
    Point e=(B-A)/d;
    Point f={-e.y,e.x};
    for(int i=1;i<=3;i++){
        Point v=p[i]-O;
        p[i]={dot(v,e)/a,dot(v,f)/b};
    }
    double ans=area()*a*b;
    cout<<fixed<<setprecision(2)<<ans<<endl;
    return 0;
}