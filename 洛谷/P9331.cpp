#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = 2e6+5;
const int MAXE = 2e7+5;
const int INF = 1e8;

int n,nodecnt;
int dis[MAXT];
bool vis[MAXT];
int dist[MAXT];

int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cnt=1;

struct node{
    int pos;
    int d;
};
struct compare{
    bool operator()(node a,node b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void build(int l,int r,int i){
    if(l==r){
        nodecnt=max(nodecnt,i+2*n);
        addedge(l,i+2*n,0);
        return ;
    }
    else{
        int mid=(l+r)>>1;
        addedge((i<<1)+2*n,i+2*n,0);
        addedge((i<<1|1)+2*n,i+2*n,0);
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i+2*n,jobv,0);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

void dijkstra(int st){
    for(int i=1;i<=nodecnt;i++){
        dis[i]=INF;
        vis[i]=0;
    }
    dis[st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int u=tmp.pos;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
    for(int i=1;i<=nodecnt;i++){
        dist[i]=(dis[i]<INF)?(dist[i]+dis[i]):INF;
    }
}

void compute(){
    for(int i=1;i<=2*n;i++){
        if(dist[i]<INF){
            heap.push({i,dist[i]});
        }
    }
    for(int i=1;i<=nodecnt;i++){
        vis[i]=false;
    }
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int u=tmp.pos;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        dist[u]=tmp.d;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&tmp.d+w<dist[v]){
                heap.push({v,tmp.d+w});
            }
        }
    }
}

int main()
{
    n=read();
    nodecnt=2*n;
    build(1,n,1);
    for(int i=1;i<=n;i++){
        int l,r;
        l=read(),r=read();
        addedge(i+n,i,1);
        add(l,r,i+n,1,n,1);
    }
    dijkstra(1);
    dijkstra(n);
    compute();

    int q=read();
    while(q--){
        int x=read();
        cout<<(dist[x]<INF?dist[x]:-1)<<endl;
    }
    return 0;
}