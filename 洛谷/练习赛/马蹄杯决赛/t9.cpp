#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = 4e5+5;
const int INF = 1e15;

int ans;
int n,m,k,t;
int dis[MAXN][32];
bool vis[MAXN][32];

int limit[MAXN];
int val[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

struct node{
    int pos,sta,dis; 
};
struct compare{
    bool operator()(node a,node b){
        return a.dis>b.dis;
    }
};
priority_queue<node,vector<node>,compare>heap;

void prepare(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
    for(int i=1;i<=n;i++){
        for(int s=0;s<32;s++){
            dis[i][s]=INF;
            vis[i][s]=false;
        }

        limit[i]=0;
        val[i]=0;
    }
    while(!heap.empty()){
        heap.pop();
    }
    ans=-1;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(){
    dis[1][0]=0;
    heap.push({1,0,0});
    while(!heap.empty()){
        node u=heap.top();
        heap.pop();
        int pos=u.pos;
        int sta=u.sta;
        int d=u.dis;
        if(pos==n){
            ans=d;
            break;
        }
        if(vis[pos][sta]){
            continue;
        }
        vis[pos][sta]=true;
        for(int i=head[pos];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if((limit[v]&sta)==limit[v]){
                int stat=(sta|val[v]);
                if(!vis[v][stat]&&dis[v][stat]>=w+d){
                    dis[v][stat]=w+d;
                    heap.push({v,stat,dis[v][stat]});
                }
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>k>>t;
        prepare();
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            addedge(u,v,w);
            addedge(v,u,w);
        }
        for(int i=1;i<=k;i++){
            int u;
            cin>>u;
            val[u]=(1<<(i-1));
        }
        for(int i=1;i<=t;i++){
            int u,v;
            cin>>u>>v;
            limit[v]|=val[u];
        }
        dijkstra();
        if(ans==-1){
            cout<<"impossible"<<endl;
        }
        else{
            cout<<ans<<endl;
        }
    }
    return 0;
}
/*
3
4 3 2 1
1 2 3
2 3 4
3 4 5
2 3
3 2
4 5 2 1
1 2 2
1 3 2
2 3 4
2 4 3
3 4 1
2 3
2 3
4 5 2 1
1 2 2
1 3 2
2 3 4
2 4 10
3 4 1
2 3
2 3
*/