// https://www.luogu.com.cn/problem/P2521
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