// https://www.luogu.com.cn/problem/P4385
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
