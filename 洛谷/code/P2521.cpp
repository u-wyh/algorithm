// https://www.luogu.com.cn/problem/P2521
// 输入：第一行三个整数 n, x, y，分别表示河边城市 (0,0)、(n,0) 以及首都 (x,y)。
// 输入：第二行一个整数 m，表示非河边且非首都的城市数量。
// 输入：接下来 m 行，每行两个整数 a, b，表示第 i 个城市坐标为 (a,b)，横坐标在 (0,n) 内且纵坐标大于 0。
// 输入：再一行一个整数 q，表示操作与询问总数。
// 输入：接下来 q 行，每行要么是 1 u（撤销第 u 个城市的保护），要么是 2（询问最小总花费）。
// 题意：x 轴是天然河流防线，不需修建也不花钱。
// 题意：(0,0)、(n,0) 和首都 (x,y) 这三个点始终必须被保护，其余城市初始都需要被保护。
// 题意：防线是一条连接 (0,0) 到 (n,0) 的折线，必须把所有当前需要保护的城市都围在防线内（含边界上）。
// 题意：单位长度防线的修建费用为 1。
// 输出：对每个询问 2，输出一行一个实数，表示修建防线的最小总花费，保留两位小数。
// 数据范围：1 <= m <= 10^5
// 数据范围：1 <= q <= 2 * 10^5
// 数据范围：1 < n <= 10^4
// 数据范围：所有点坐标范围均在 10^4 以内，且保证没有重合的点
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m,q;

bool del[MAXN];

struct Point{
    int x,y;
    bool operator<(const Point &b)const{
        return x<b.x;
    }
};
Point p[MAXN];
set<Point>st;

double ans;
double res[MAXN];

struct Query{
    int op,id;
};
Query query[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

double dis(Point a,Point b){
    return sqrt(1.0*(a.x-b.x)*(a.x-b.x)+1.0*(a.y-b.y)*(a.y-b.y));
}

// 删除上凸壳上的一个非端点
void erasePoint(set<Point>::iterator it){
    auto l=prev(it),r=next(it);

    ans-=dis(*l,*it)+dis(*it,*r);
    ans+=dis(*l,*r);

    st.erase(it);
}

void insertPoint(Point a){
    auto r=st.lower_bound(a);
    if(r->x==a.x){
        if(r->y >=a.y){
            return ;
        }
        erasePoint(r);
        r=st.lower_bound(a);
    }

    auto l=prev(r);

    if(cross(*r-*l,a-*l)<=0){
        return ;
    }

    ans+=dis(*l,a)+dis(a,*r)-dis(*l,*r);

    auto it=st.insert(a).first;
    while(prev(it)!=st.begin()){
        auto b=prev(it),c=prev(b);
        if(cross(*b-*c,*it-*b)<0){
            break;
        }
        erasePoint(b);
    }
    while(next(next(it))!=st.end()){
        auto b=next(it),c=next(b);
        if(cross(*b-*it,*c-*b)<0){
            break;
        }
        erasePoint(b);
    }
}

signed main()
{
    Point C;
    cin>>n>>C.x>>C.y;
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>p[i].x>>p[i].y;
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>query[i].op;
        if(query[i].op==1){
            cin>>query[i].id;
            del[query[i].id]=true;
        }
    }

    st.insert({0,0});
    st.insert({n,0});
    ans=n;
    insertPoint(C);

    for(int i=1;i<=m;i++){
        if(!del[i]){
            insertPoint(p[i]);
        }
    }

    for(int i=q;i>=1;i--){
        if(query[i].op==1){
            int id=query[i].id;
            insertPoint(p[id]);
        }
        else{
            res[i]=ans;
        }
    }

    cout<<fixed<<setprecision(2);
    for(int i=1;i<=q;i++){
        if(query[i].op==2){
            cout<<res[i]<<endl;
        }
    }
    return 0;
}