// https://www.luogu.com.cn/problem/P4418
// 题意：平面上有 n 条线段表示战壕（可重叠或共享端点），
// 安排 3 名警卫在战壕上，使两两之间连线完全被战壕覆盖且该线段上不含第三名警卫，
// 求放置方案数。
// 数据范围：1 <= n <= 20，端点坐标为不超过 1000 的正整数。
// 难度评分：1900（洛谷分级换算）
// 算法标签：计算几何、枚举
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const double eps = 1e-8;

int n,m;
struct Point{
    double x,y;
};
struct Line{
    Point a,b;
};
struct Interval{
    double l,r;
};

Line s[25];
Point p[MAXN];
bool vis[MAXN][MAXN];

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

bool same(Point a,Point b){
    return fabs(a.x-b.x)<eps &&
           fabs(a.y-b.y)<eps;
}

void add(Point a){
    // 候选点去重
    for(int i=1;i<=m;i++){
        if(same(p[i],a)) return;
    }
    p[++m]=a;
}

void get_intersection(Line a,Line b){
    Point d=a.b-a.a;
    Point e=b.b-b.a;
    double den=cross(d,e);

    // 平行或共线，不产生新的交点
    if(fabs(den)<eps) return;

    Point v=b.a-a.a;

    // a.a+t*d = b.a+u*e
    double t=cross(v,e)/den;
    double u=cross(v,d)/den;

    // 判断交点是否在线段范围内
    if(t<-eps || t>1+eps ||
       u<-eps || u>1+eps) return;

    add(a.a+d*t);
}

bool visible(Point a,Point b){
    Interval q[25];
    int cnt=0;

    bool flag=(fabs(a.x-b.x)>eps);

    for(int i=1;i<=n;i++){
        Point x=s[i].a;
        Point y=s[i].b;

        // 判断战壕是否与 AB 共线
        if(fabs(cross(b-a,x-a))>eps ||
           fabs(cross(b-a,y-a))>eps) continue;

        double t1,t2,l,r;

        // 非竖直线段，使用 x 坐标
        if(flag){
            t1=x.x;
            t2=y.x;
            l=min(a.x,b.x);
            r=max(a.x,b.x);
        }
        // 竖直线段，使用 y 坐标
        else{
            t1=x.y;
            t2=y.y;
            l=min(a.y,b.y);
            r=max(a.y,b.y);
        }

        // 求战壕与 AB 的一维区间交集
        double L=max(l,min(t1,t2));
        double R=min(r,max(t1,t2));

        if(L<=R+eps){
            q[++cnt]={L,R};
        }
    }

    sort(q+1,q+cnt+1,[](Interval a,Interval b){
        return a.l<b.l;
    });

    double now=flag?min(a.x,b.x):min(a.y,b.y);
    double ed=flag?max(a.x,b.x):max(a.y,b.y);

    for(int i=1;i<=cnt;i++){
        if(q[i].l>now+eps) return false;
        now=max(now,q[i].r);
        if(now>=ed-eps) return true;
    }

    return false;
}

bool between(Point a,Point b,Point c){
    Point d=b-a;
    double len=dot(d,d);

    // 判断三个点是否共线
    if(fabs(cross(d,c-a))>eps) return false;

    // 判断 C 是否在线段 AB 的内部
    double t=dot(c-a,d)/len;
    return t>eps && t<1-eps;
}

int main()
{
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>s[i].a.x>>s[i].a.y
           >>s[i].b.x>>s[i].b.y;

        // 加入所有线段端点
        add(s[i].a);
        add(s[i].b);
    }

    // 枚举线段，求出所有非平行交点
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            get_intersection(s[i],s[j]);
        }
    }

    // 预处理任意两个候选点是否可见
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            vis[i][j]=vis[j][i]=visible(p[i],p[j]);
        }
    }

    int ans=0;

    // 枚举三个警卫的位置
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            if(!vis[i][j]) continue;

            for(int k=j+1;k<=m;k++){
                // 三对警卫必须两两可见
                if(!vis[i][k] || !vis[j][k]) continue;

                // 不能有第三个警卫位于另外两人之间
                if(between(p[i],p[j],p[k])) continue;
                if(between(p[i],p[k],p[j])) continue;
                if(between(p[j],p[k],p[i])) continue;

                ans++;
            }
        }
    }

    cout<<ans<<'\n';
    return 0;
}
