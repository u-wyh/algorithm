#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXV = 505;
const int MAXE = 1e6+5;
const int INF = 1e9;

int n,m,s,t,k,l;
int mincost,maxflow;
int cnt1[MAXN];
int cnt2[MAXN];

queue<int>q;
bool in[MAXV];

int pot[MAXV];
int dis[MAXV];
int pre[MAXV];
bool vis[MAXV];

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int cost[MAXE];
int cnt=2;

vector<int>vec1[MAXN];
vector<int>vec2[MAXN];
int cnt3[MAXN];
int pp[MAXN];
int qq[MAXN];
vector<int>aa[MAXN];
vector<int>bb[MAXN];

struct cmp{
    bool operator()(pair<int,int>&a,pair<int,int>&b){
        return a.first>b.first;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

inline void addedge(int u,int v,int w,int c){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    cost[cnt]=c;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    cost[cnt]=-c;
    head[v]=cnt++;
}

void spfa(int s){
    for(int i=1;i<=t;i++){
        pot[i]=INF;
    }

    q.push(s);
    pot[s]=0;
    in[s]=1;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int c=cost[i];

            if(w>0&&pot[u]+c<pot[v]){
                pot[v]=pot[u]+c;
                if(!in[v]){
                    q.push(v);
                    in[v]=true;
                }
            }
        }
    }
}

bool dijkstra(){
    for(int i=1;i<=t;i++){
        dis[i]=INF;
        pre[i]=-1;
        vis[i]=false;
    }

    dis[s]=0;
    heap.push({0,s});
    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int residual=cap[i];
            int c_original=cost[i];
            if(residual<=0){
                continue;
            }
            int adjusted_cost=c_original+pot[u]-pot[v];
            if(dis[u]+adjusted_cost<dis[v]){
                dis[v]=dis[u]+adjusted_cost;
                pre[v]=i;
                heap.push({dis[v],v});
            }
        }
    }
    return dis[t]<INF;
}

void mincostmaxflow(){
    spfa(s);
    maxflow=0;
    mincost=0;
    while(dijkstra()){
        int flow=INF;
        for(int u=t;u!=s;u=to[pre[u]^1]){
            flow=min(flow,cap[pre[u]]);
        }
        maxflow+=flow;
        mincost+=flow*(dis[t]+pot[t]);
        for(int u=t;u!=s;u=to[pre[u]^1]){
            cap[pre[u]]-=flow;
            cap[pre[u]^1]+=flow;
        }
        for(int i=1;i<=t;i++){
            if(dis[i]<INF){
                pot[i]+=dis[i];
            }
        }
    }
}

int main()
{
    cin>>n>>m>>k>>l;
    s=2*n+2*m+1;
    t=s+1;

    for(int i=1;i<=k;i++){
        int id;
        cin>>id;
        cnt1[id]++;
    }
    for(int i=1;i<=l;i++){
        int y;
        cin>>y;
        cnt2[y]++;
    }

    for(int i=1;i<=n;i++){
        addedge(s,i,cnt1[i],0);
    }
    for(int i=1;i<=n;i++){
        addedge(i+n,t,cnt2[i],0);
    }

    for(int i=1;i<=m;i++){
        cin>>cnt3[i]>>pp[i]>>qq[i];
        for(int j=1;j<=pp[i];j++){
            int v;
            cin>>v;
            vec1[v].push_back(i);
            aa[i].push_back(v);
        }
        for(int j=1;j<=qq[i];j++){
            int v;
            cin>>v;
            vec2[v].push_back(i);
            bb[i].push_back(v);
        }
    }

    for(int i=1;i<=m;i++){
        addedge(2*n+i,2*n+m+i,cnt3[i],1);
        for(int j=1;j<=qq[i];j++){
            int v=bb[i][j-1];
            for(int k=0;k<(int)vec1[v].size();k++){
                int to=vec1[v][k];
                addedge(2*n+m+i,2*n+to,cnt3[i],0);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<(int)vec1[i].size();j++){
            int to=vec1[i][j];
            addedge(i,2*n+to,cnt1[i],0);
        }
        for(int j=0;j<(int)vec2[i].size();j++){
            int to=vec2[i][j];
            addedge(2*n+m+to,n+i,cnt2[i],0);
        }
    }
    for(int i=1;i<=n;i++){
        addedge(i,i+n,cnt1[i],0);
    }
    

    mincostmaxflow();
    if(maxflow!=k){
        cout<<-1<<endl;
    }
    else{
        cout<<mincost<<endl;
    }
    return 0;
}