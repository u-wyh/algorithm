// https://onlinejudge.org/external/3/378.pdf
// 题意：给 n 组询问，每组给两条直线上各两点的坐标。
// 输出：按题面格式输出首行和末行。
// 重合时输出 LINE，平行无交点时输出 NONE。
// 有唯一交点时输出 POINT 和保留两位小数的坐标。
// 数据范围：1 <= n <= 10。
// 坐标为 [-1000, 1000] 内整数，同一直线的两点不同。
// 难度评分：1300（估算）
// 算法标签：计算几何
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;

struct Point{
    double x,y;
};

Point a,b,c,d,u,v;

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

// 叉积
double operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

// 向量数乘
Point operator*(Point a,double t){
    return {a.x*t,a.y*t};
}

double cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

// 求两条直线的交点
Point getnode(Point a,Point u,Point b,Point v){
    double t=((b-a)*v)/(u*v);
    return a+u*t;
}

void solve(){
    cin>>a.x>>a.y>>b.x>>b.y;
    cin>>c.x>>c.y>>d.x>>d.y;

    u=b-a;
    v=d-c;

    if(fabs(u*v)<eps){
        // 两条直线平行
        if(fabs(cross(a,b,c))<eps){
            cout<<"LINE"<<endl;
        }
        else{
            cout<<"NONE"<<endl;
        }
    }
    else{
        // 两条直线相交
        Point p=getnode(a,u,c,v);

        if(fabs(p.x)<0.005) p.x=0;
        if(fabs(p.y)<0.005) p.y=0;

        cout<<"POINT "<<fixed<<setprecision(2)
            <<p.x<<" "<<p.y<<endl;
    }
}

int main(){
    int T;
    cin>>T;

    cout<<"INTERSECTING LINES OUTPUT"<<endl;

    while(T--){
        solve();
    }

    cout<<"END OF OUTPUT"<<endl;
    return 0;
}