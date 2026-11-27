// https://www.luogu.com.cn/problem/P3268
// 题意：输入圆的数量 N，以及每个圆的圆心与半径 (x, y, r)，保证任意两圆无交点（只相离或包含）。
// 统计平面上被奇数个圆覆盖区域的面积之和（异或面积并）。
// 输出异或面积并除以 π 后的整数值。
// 数据范围：1 <= N <= 2*10^5，|x_i|, |y_i| <= 10^8，0 < r <= 10^6。
#include<bits/stdc++.h>
// 算法标签：扫描线、计算几何
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
struct Circle{
    int x,y,r;
};
Circle circle[MAXN];
struct Event{
    int x,id,op;
};
Event event[MAXN<<1];

struct Arc{
    int id,op;
};

int dep[MAXN];
int nowx;

long double gety(Arc a){
    int dx=nowx-circle[a.id].x;
    int v=circle[a.id].r*circle[a.id].r-dx*dx;
    return (long double)circle[a.id].y+a.op*sqrt(max(0ll,v));
}

struct Cmp{
    bool operator()(Arc a,Arc b)const{
        if(a.id==b.id){
            return a.op<b.op;
        }
        long double ya=gety(a);
        long double yb=gety(b);
        return ya<yb;
    }
};

set<Arc,Cmp>st;

bool cmp(Event a,Event b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.op<b.op;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>circle[i].x>>circle[i].y>>circle[i].r;
        event[2*i-1]={circle[i].x-circle[i].r,i,1};
        event[2*i]={circle[i].x+circle[i].r,i,-1};
    }
    sort(event+1,event+2*n+1,cmp);

    int ans=0;
    for(int i=1;i<2*n;i++){
        int id=event[i].id;
        nowx=event[i].x;
        if(event[i].op==-1){
            st.erase({id,1});
            st.erase({id,-1});
        }
        else{
            auto it=st.insert({id,-1}).first;
            if(it==st.begin()){
                dep[id]=1;
            }
            else{
                --it;
                if(it->op==-1){
                    dep[id]=dep[it->id]+1;
                }
                else{
                    dep[id]=dep[it->id];
                }
            }
            st.insert({id,1});
            int area=circle[id].r*circle[id].r;
            if(dep[id]&1){
                ans+=area;
            }
            else{
                ans-=area;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}