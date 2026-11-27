// https://www.luogu.com.cn/problem/P3493
// 题意：凸多边形岛屿岸上有 n 个顺时针编号 1..n 的城市，1 号为首都，人在 n 号。
// 题意：任意两城之间均有直路相连，道路交点处可以自由转向穿行。
// 题意：有 m 条路被游击队控制不能沿路走，但可穿过其与安全路的交点。
// 题意：求从起点城市到终点城市（1 与 n 间）的最短安全路径长度。
// 输入：（原题面 main.edu.pl 外链图不可达，据洛谷 P3493 讨论区补充整理）
// 输入：第一行输入城市数 n 和受控道路数 m；接下来 n 行输入各城市坐标 x, y。
// 输入：接下来 m 行每行输入 u, v，表示 u 与 v 之间的直路不可走，保证有解。
// 输出：输出一个实数表示最短距离，绝对误差不超过 10^-5。
// 数据范围：3 <= n <= 10^5，1 <= m <= 10^6，|x|, |y| <= 10^6（源自洛谷讨论区及 AC 题解）。
#include<bits/stdc++.h>
// 算法标签：半平面交、贪心、计算几何
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;
const long double eps = 1e-9;
const long double PI = acosl(-1.0);

int n,m;
struct Point{
    long double x,y;
};
Point city[MAXN];

struct Line{
    Point s,e;
};
Line l[MAXN],q[MAXN];
Point p[MAXN];
int lcnt,cnt;

struct Ban{
    int u,v;
};
Ban ban[MAXM];
int mark[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

long double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

long double dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

Point operator+(Point a,Point b){
    return {a.x+b.x,a.y+b.y};
}

Point operator*(Point a,long double k){
    return {a.x*k,a.y*k};
}

long double angle(Line a){
    return atan2l(a.e.y-a.s.y,a.e.x-a.s.x);
}

bool cmp(Line a,Line b){
    long double x=angle(a),y=angle(b);
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

bool cmp2(Ban a,Ban b){
    return a.u<b.u;
}

// 求两条直线的交点
Point getNode(Point a,Point u,Point b,Point v){
    long double t=cross(b-a,v)/cross(u,v);
    return a+u*t;
}

Point getNode(Line a,Line b){
    return getNode(a.s,a.e-a.s,b.s,b.e-b.s);
}

long double len(Point a){
    return sqrtl(a.x*a.x+a.y*a.y);
}

// 判断直线 b、c 的交点是否在直线 a 的右侧
bool right(Line a,Line b,Line c){
    Point t=getNode(b,c);
    return cross(a.e-a.s,t-a.s)<-eps*len(a.e-a.s);
}

long double half_plane(){
    cnt=0;
    sort(l+1,l+lcnt+1,cmp);
    int k=0;
    for(int i=1;i<=lcnt;i++){
        Point v=l[i].e-l[i].s;

        if(k>0&&cross(l[k].e-l[k].s,v)==0&&dot(l[k].e-l[k].s,v)>0){
            if(cross(l[k].e-l[k].s,l[i].s-l[k].s)>0){
                l[k]=l[i];
            }
        }
        else{
            l[++k]=l[i];
        }
    }
    lcnt=k;

    int h=1,t=0;
    for(int i=1;i<=lcnt;i++){

        // 队尾两条直线的交点不满足新半平面，弹出队尾
        while(t-h+1>=2&&right(l[i],q[t-1],q[t])){
            t--;
        }

        // 队首两条直线的交点不满足新半平面，弹出队首
        while(t-h+1>=2&&right(l[i],q[h],q[h+1])){
            h++;
        }

        // 避免相邻反向平行直线导致交点不存在
        if(t>=h&&cross(q[t].e-q[t].s,l[i].e-l[i].s)==0){
            return 0;
        }

        q[++t]=l[i];
    }

    // 首尾约束也必须相互满足
    while(t-h+1>=3&&right(q[h],q[t-1],q[t])){
        t--;
    }
    while(t-h+1>=3&&right(q[t],q[h],q[h+1])){
        h++;
    }

    k=t-h+1;
    if(k<3){
        return 0;
    }

    // 相邻直线求交，得到交域的顶点
    for(int i=0;i<k;i++){
        Line a=q[h+i];
        Line b=q[h+(i+1)%k];

        if(cross(a.e-a.s,b.e-b.s)==0){
            return 0;
        }

        p[i+1]=getNode(a,b);
    }

    cnt=k;

    // 计算半平面交多边形的周长
    long double res=0;
    for(int i=1;i<=cnt;i++){
        res+=len(p[i%cnt+1]-p[i]);
    }
    return res;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>city[i].x>>city[i].y;
    }
    bool flag=true;
    for(int i=1;i<=m;i++){
        cin>>ban[i].u>>ban[i].v;
        if(ban[i].u>ban[i].v){
            swap(ban[i].u,ban[i].v);
        }
        if(ban[i].u==1 && ban[i].v==n){
            flag=false;
        }
    }

    cout<<fixed<<setprecision(10);
    if(flag){
        cout<<len(city[n]-city[1])<<endl;
        return 0;
    }

    sort(ban+1,ban+m+1,cmp2);
    int ptr=1;
    for(int i=1;i<=n;i++){
        while(ptr<=m && ban[ptr].u==i){
            mark[ban[ptr].v]=i;
            ptr++;
        }

        int j=n;
        while(j>i&&mark[j]==i){
            j--;
        }

        if(j>i){
            l[++lcnt]={city[j],city[i]};
        }
    }
    l[++lcnt]={city[1],city[n]};

    long double ans=half_plane()-len(city[n]-city[1]);
    cout<<ans<<endl;
    return 0;
}