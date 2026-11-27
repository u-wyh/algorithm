// https://www.luogu.com.cn/problem/P5696
// 题意：多组数据，按顺时针给出一个 n 边形房间顶点坐标，
// 判断房间内是否存在一点能直线监视到整个房间内部（多边形核非空）。
// 输入若干组 n 及 n 个顶点坐标（n=0 结束）；
// 每组按格式输出编号及是否可监视的结果。
// 数据范围：4 <= n <= 100，
// -10000 <= x, y <= 10000。
// 算法标签：半平面交、计算几何
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const double eps = 1e-9;
const double PI = acos(-1);

struct Point{
    double x,y;
};
struct Line{
    Point s,e;
};

int n;
Point p[MAXN];
int lcnt;
Line l[MAXN];
Line q[MAXN];

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

Point operator*(Point a,double k){
    return {a.x*k,a.y*k};
}

Point operator/(Point a,double k){
    return {a.x/k,a.y/k};
}

double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double len2(Point a){
    return dot(a,a);
}

double len(Point a){
    return sqrt(len2(a));
}

Point getNode(Point a,Point u,Point b,Point v){
    double du=len(u),dv=len(v);
    u=u/du;
    v=v/dv;
    double d=cross(u,v);
    return a+u*(cross(b-a,v)/d);
}

Point getNode(Line a,Line b){
    return getNode(a.s,a.e-a.s,b.s,b.e-b.s);
}

double angle(Line a){
    return atan2(a.e.y-a.s.y,a.e.x-a.s.x);
}

bool cmp(Line a,Line b){
    double x=angle(a),y=angle(b);
    if(x==-PI){
        x=PI;
    }
    if(y==-PI){
        y=PI;
    }
    if(x!=y){
        return x<y;
    }
    if(a.s.x!=b.s.x){
        return a.s.x<b.s.x;
    }
    if(a.s.y!=b.s.y){
        return a.s.y<b.s.y;
    }
    if(a.e.x!=b.e.x){
        return a.e.x<b.e.x;
    }
    return a.e.y<b.e.y;
}

bool right(Line a,Line b,Line c){
    Point t=getNode(b,c);
    return cross(a.e-a.s,t-a.s)<-eps*len(a.e-a.s);
}

Point v[MAXN];

double half_plane(){
    for(int i=1;i<=lcnt;i++){
        if(len(l[i].e-l[i].s)<=eps){
            return 0;
        }
    }
    sort(l+1,l+lcnt+1,cmp);

    int m=0;
    for(int i=1;i<=lcnt;i++){
        Point v=l[i].e-l[i].s;
        if(m>0&&cross(l[m].e-l[m].s,v)==0&&dot(l[m].e-l[m].s,v)>0){
            if(cross(l[m].e-l[m].s,l[i].s-l[m].s)>0){
                l[m]=l[i];
            }
        }else{
            l[++m]=l[i];
        }
    }
    lcnt=m;

    int h=1,t=0;
    for(int i=1;i<=lcnt;i++){
        while(t-h+1>=2&&right(l[i],q[t-1],q[t])){
            t--;
        }
        while(t-h+1>=2&&right(l[i],q[h],q[h+1])){
            h++;
        }
        if(t>=h&&cross(q[t].e-q[t].s,l[i].e-l[i].s)==0){
            return 0;
        }
        q[++t]=l[i];
    }

    while(t-h+1>=3&&right(q[h],q[t-1],q[t])){
        t--;
    }
    while(t-h+1>=3&&right(q[t],q[h],q[h+1])){
        h++;
    }

    int k=t-h+1;
    if(k<3){
        return 0;
    }

    for(int i=0;i<k;i++){
        Line a=q[h+i],b=q[h+(i+1)%k];
        if(cross(a.e-a.s,b.e-b.s)==0){
            return 0;
        }
        v[i+1]=getNode(a,b);
    }

    double sum=0;
    for(int i=2;i<k;i++){
        sum+=cross(v[i]-v[1],v[i+1]-v[1]);
    }
    if(fabs(sum)<=eps){
        return 0;
    }

    return fabs(sum)/2;
}

Line ori[MAXN];

bool check(int i,int j){
    Line a=ori[i],b=ori[j];

    // 平行直线没有唯一交点
    if(fabs(cross(a.e-a.s,b.e-b.s))<eps){
        return false;
    }

    // 求两条直线的交点
    Point p=getNode(a,b);

    // 判断交点是否满足所有半平面
    for(int k=1;k<=n;k++){
        Line c=ori[k];
        if(cross(c.e-c.s,p-c.s)<-eps*len(c.e-c.s)){
            return false;
        }
    }

    return true;
}


bool possible(){
    if(half_plane()>0){
        return true;
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(check(i,j)){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int t=0;
    while(cin>>n && n){
        for(int i=1;i<=n;i++){
            cin>>p[i].x>>p[i].y;
        }
        p[n+1]=p[1];
        lcnt=n;
        for(int i=1;i<=n;i++){
            l[i]={p[i+1],p[i]};
            ori[i]=l[i];
        }

        bool ans=possible();

        if(t){
            cout<<endl;
        }
        cout<<"Room #"<<++t<<":"<<endl;
        if(ans){
            cout<<"Surveillance is possible.\n";
        }else{
            cout<<"Surveillance is impossible.\n";
        }
    }
    return 0;
}