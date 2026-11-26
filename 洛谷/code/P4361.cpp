// https://www.luogu.com.cn/problem/P4361
// 题意：平面上有 1 个定向激光发射装置（起点与方向）和 n 条互不相交的激光偏转线段
// 光线击中线段（不平行且含端点）按出射角 beta = (a/b)*alpha 偏转（beta > pi/2 时可能偏转到另一面）
// 求依次照射到的偏转装置编号（最多前 10 次，未偏转输出 NONE）。
// 数据范围：n <= 100，所有坐标及 a, b 的绝对值 <= 1000，a, b 非零，方向向量非零，线段无交点且起点不在任何线段上。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const long double eps = 1e-12L;

int n;
struct Point{
    long double x,y;
};
struct Segment{
    Point a,b;
    long double lambda;
};
Segment seg[MAXN];

int ans[15],cnt;

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator*(Point a,long double k){
    return {a.x*k,a.y*k};
}

Point operator/(Point a,long double k){
    return {a.x/k,a.y/k};
}

long double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

long double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

long double len(Point a){
    return sqrtl(dot(a,a));
}

Point rotate(Point a,long double t){
    return {
        a.x*cosl(t)-a.y*sinl(t),
        a.x*sinl(t)+a.y*cosl(t)
    };
}

// 求射线与第 id 条线段的交点参数 t
bool intersect(Point o,Point d,int id,long double &t){
    Point a=seg[id].a;
    Point s=seg[id].b-a;

    long double den=cross(d,s);
    if(fabsl(den)<eps) return false;

    Point w=a-o;
    t=cross(w,s)/den;
    long double u=cross(w,d)/den;

    return t>eps&&u>=-eps&&u<=1+eps;
}

// 计算发生偏转之后的方向
Point reflect(Point d,int id){
    Point s=seg[id].b-seg[id].a;
    Point normal={-s.y,s.x};

    // 法向量指向激光入射的一侧
    if(dot(normal,d)>0){
        normal=normal*(-1);
    }
    normal=normal/len(normal);

    // 反向入射光线与法向量的有向夹角
    Point back=d*(-1);
    long double alpha=atan2l(
        cross(normal,back),
        dot(normal,back)
    );

    // 出射方向相对法向量旋转 -lambda*alpha
    return rotate(normal,-seg[id].lambda*alpha);
}

int main(){
    Point o,d;
    cin>>o.x>>o.y>>d.x>>d.y;
    d=d/len(d);

    cin>>n;
    for(int i=1;i<=n;i++){
        long double a,b;
        cin>>seg[i].a.x>>seg[i].a.y;
        cin>>seg[i].b.x>>seg[i].b.y;
        cin>>a>>b;
        seg[i].lambda=a/b;
    }

    int last=0;

    for(int k=1;k<=10;k++){
        int id=0;
        long double best=1e100L;

        // 找到射线最先碰到的线段
        for(int i=1;i<=n;i++){
            if(i==last) continue;

            long double t;
            if(intersect(o,d,i,t)&&t<best){
                best=t;
                id=i;
            }
        }

        if(!id) break;

        ans[++cnt]=id;

        // 更新激光的位置与方向
        o=o+d*best;
        d=reflect(d,id);
        last=id;
    }

    if(!cnt){
        cout<<"NONE\n";
    }
    else{
        for(int i=1;i<=cnt;i++){
            if(i>1) cout<<' ';
            cout<<ans[i];
        }
        cout<<'\n';
    }

    return 0;
}
