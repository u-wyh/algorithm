// https://www.luogu.com.cn/problem/P4385
// 输入：第一行一个整数 N，表示总点数。
// 输入：接下来 N 行，
// 每行两个整数 x_i, y_i 和一个字符 R（红点）或 B（蓝点）。
// 题意：在平面上找一对平行线（方向任意，不要求平行于坐标轴）。
// 题意：要求平行线不经过任何给定的点，且两条平行线之间不能包含任何蓝点。
// 题意：使被夹在这对平行线之间的红点个数尽量多。
// 输出：输出一个整数，表示夹在平行线之间的最大红点数量。
// 数据范围：1 <= N <= 1000
// 数据范围：|x_i|, |y_i| <= 10^9
// 数据范围：保证不存在三点共线
// 算法标签：计算几何、极角排序、扫描线
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e3+5;
const int MAXM = MAXN*MAXN/2;

int n;
struct Point{
    int x,y;
    char c;
};
Point p[MAXN];

struct Event{
    int x,y,u,v;
};
Event e[MAXM];
int cnt;

int pos[MAXN];

set<int>st;
int ans=0;

bool cmp1(Point a,Point b){
    if(a.y!=b.y){
        return a.y<b.y;
    }
    return a.x<b.x;
}

int cross(Event a,Event b){
    return a.x*b.y-a.y*b.x;
}

bool cmp2(Event a,Event b){
    return cross(a,b)>0;
}

void update(int x){
    if(p[x].c=='B'){
        return ;
    }
    auto it=st.lower_bound(pos[x]);
    int r=*it;
    int l=*prev(it);
    ans=max(ans,r-l-1);
}

void change(int x,int y){
    if(p[x].c!=p[y].c){
        if(p[x].c=='B'){
            st.erase(pos[x]);
            st.insert(pos[y]);
        }
        else{
            st.erase(pos[y]);
            st.insert(pos[x]);
        }
    }
    swap(pos[x],pos[y]);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y>>p[i].c;
    }
    sort(p+1,p+n+1,cmp1);

    st.insert(0);
    st.insert(n+1);
    for(int i=1;i<=n;i++){
        pos[i]=i;
        if(p[i].c=='B'){
            st.insert(i);
        }
    }
    for(int i=1;i<=n;i++){
        update(i);
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int dx=p[j].x-p[i].x;
            int dy=p[j].y-p[i].y;
            e[++cnt]={dx,dy,i,j};
        }
    }
    sort(e+1,e+cnt+1,cmp2);

    int j=1;
    for(int i=1;i<=cnt;i=j+1){
        j=i;
        while(j+1<=cnt && cross(e[i],e[j+1])==0){
            j++;
        }
        for(int k=i;k<=j;k++){
            change(e[k].u,e[k].v);
        }
        for(int k=i;k<=j;k++){
            update(e[k].u);
            update(e[k].v);
        }
    }
    cout<<ans<<endl;
    return 0;
}
