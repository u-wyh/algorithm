// https://www.luogu.com.cn/problem/CF1932G
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 1e18;

int n,m,H;
int l[MAXN];
int s[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int t[MAXN<<1];
int dt[MAXN<<1];
int cntg=1;

int dis[MAXN];
bool vis[MAXN];

struct node{
    int u,d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        dis[i]=INF;
        vis[i]=false;
    }
    cntg=1;
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    t[cntg]=-1;
    head[u]=cntg++;
}

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

inline void calc(int u,int v,int i){
    if(s[u]==s[v]){
        if(l[u]==l[v]){
            t[i]=0;
            dt[i]=1;
        }
        else{
            t[i]=dt[i]=INF;
        }
    }
    else{
        int a=s[u]-s[v];
        int c=l[v]-l[u];
        if(a<0){
            a=-a;
            c=-c;
        }

        exgcd(a,H);
        if(c%d!=0){
            t[i]=dt[i]=INF;
        }
        else{
            dt[i]=H/d;
            x=c/d*x;
            t[i]=((x%dt[i])+dt[i])%dt[i];
        }
    }
}

void dijkstra(){
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().u;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int tim=t[i];
            int d=dt[i];
            int tt=dis[u];
            if(tim>=tt){
                
            }
            else{
                tim+=(tt-tim+d-1)/d*d;
            }
            if(dis[v]>tim+1){
                dis[v]=tim+1;
                heap.push({v,dis[v]});
            }
        }
    }
}

void solve(){
    cin>>n>>m>>H;
    init();
    for(int i=1;i<=n;i++){
        cin>>l[i];
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            calc(u,v,i);
        }
    }
    dijkstra();

    if(dis[n]==INF){
        cout<<-1<<endl;
    }
    else{
        cout<<dis[n]<<endl;
    }
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