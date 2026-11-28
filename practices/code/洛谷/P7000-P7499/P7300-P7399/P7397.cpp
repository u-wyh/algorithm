// https://www.luogu.com.cn/problem/P7397
// 题意：T 组数据，每组有 n 个不重叠的边平行坐标轴的建筑顶层矩形，
// 以及一个 m 顶点的凸多边形降雨云（顶点无序）
// 从起始时刻到结束时刻沿 s -> e 方向以速率 v 匀速平移；
// 求降雨云扫过区域与所有建筑顶层交的总面积（误差 10^-1 内）。
// 数据范围：1 <= T <= 10^3，1 <= n <= 50，
// 3 <= m <= 100，0 < v <= 100
// 所有坐标为 [-10^5, 10^5] 内整数。
// 难度评分：2400（洛谷分级换算）
// 算法标签：计算几何、凸包、半平面交
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 405;

int n,m;

struct Point{
    double x,y;
};
Point p[MAXN];
Point hull[MAXN];
Point q[MAXN];
Point tmp[MAXN];
int cntp,cnth,cntq;

struct Rect{
    int x1,y1,x2,y2;
};
Rect rect[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

double len(Point a){
    return sqrt(a.x*a.x+a.y*a.y);
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void Andrew(){
    sort(p+1,p+cntp+1,cmp);
    cnth=0;
    for(int i=1;i<=cntp;i++){
        if(cnth==0|| p[i].x!=p[i-1].x|| p[i].y!=p[i-1].y){
            p[++cnth]=p[i];
        }
    }
    cntp=cnth,cnth=0;

    for(int i=1;i<=cntp;i++){
        while(cnth>=2 && cross(hull[cnth]-hull[cnth-1],p[i]-hull[cnth-1])<=0){
            cnth--;
        }
        hull[++cnth]=p[i];
    }
    int h=cnth;
    for(int i=cntp-1;i>=1;i--){
        while(cnth>h && cross(hull[cnth]-hull[cnth-1],p[i]-hull[cnth-1])<=0){
            cnth--;
        }
        hull[++cnth]=p[i];
    }
    cnth--;
}

Point intersect(Point a,Point b,Point s,Point t){
    // 叉积与点到直线的有向距离成正比
    double d1=cross(t-s,a-s);
    double d2=cross(t-s,b-s);

    // 根据相似三角形求出交点在线段 ab 上的位置
    return a+(b-a)*(d1/(d1-d2));
}

void cut(Point s,Point t){
    if(cntq==0){
        return ;
    }

    int cnt=0;
    q[cntq+1]=q[1];
    for(int i=1;i<=cntq;i++){
        Point a=q[i];
        Point b=q[i+1];

        double d1=cross(t-s,a-s);
        double d2=cross(t-s,b-s);
        bool f1=(d1>=0);
        bool f2=(d2>=0);

        if(f1){
            tmp[++cnt]=a;
        }
        if(f1!=f2){
            tmp[++cnt]=intersect(a,b,s,t);
        }
    }

    cntq=cnt;
    for(int i=1;i<=cnt;i++){
        q[i]=tmp[i];
    }
}

double area(){
    if(cntq<3){
        return 0;
    }
    double ans=0;
    for(int i=2;i<cntq;i++){
        ans+=cross(q[i]-q[1],q[i+1]-q[1]);
    }
    return abs(ans)/2;
}

double calc(Rect r){
    cntq=cnth;
    for(int i=1;i<=cnth;i++){
        q[i]=hull[i];
    }
    Point a={r.x1,r.y1};
    Point b={r.x2,r.y1};
    Point c={r.x2,r.y2};
    Point d={r.x1,r.y2};

    cut(a,b);
    cut(b,c);
    cut(c,d);
    cut(d,a);

    return area();
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        rect[i]={min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2)};
    }

    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>p[i].x>>p[i].y;
    }

    Point s,e;
    cin>>s.x>>s.y>>e.x>>e.y;
    int v,h1,m1,h2,m2;
    char ch;
    cin>>v>>h1>>ch>>m1>>h2>>ch>>m2;

    int tim=(h2*60+m2)-(h1*60+m1);
    Point dir=e-s;
    Point move=dir*(v*tim/len(dir));

    for(int i=1;i<=m;i++){
        p[i+m]=p[i]+move;
    }

    cntp=m*2;
    Andrew();

    double ans=0;
    for(int i=1;i<=n;i++){
        ans+=calc(rect[i]);
    }
    cout<<fixed<<setprecision(1)<<ans<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}