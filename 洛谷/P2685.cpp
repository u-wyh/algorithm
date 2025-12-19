#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 4e5+5;
const int INF = 1e18;

int n,m;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

int dis1[MAXN];
int dis2[MAXN];
int vis[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>heap;

bool inpath[MAXM<<1];
int tot;
int id[MAXN];
int path[MAXN];

int lt[MAXN];
int rt[MAXN];

int tree[MAXN<<2];

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

void dijkstra(int *dis,int st){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[st]=0;
    heap.push({0,st});
    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[u]+w<dis[v]){
                dis[v]=w+dis[u];
                heap.push({dis[v],v});
            }
        }
    }
}

void getpath(){
    int x=1;
    while(x!=n){
        path[++tot]=x;
        id[x]=tot;
        for(int i=head[x];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if((dis2[v]+w==dis2[x])&&(dis1[x]+w==dis1[v])){
                inpath[i]=true;
                x=v;
                break;
            }
        }
    }
    path[++tot]=n;
    id[n]=tot;
}

void build(int l,int r,int i){
    tree[i]=INF;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        tree[i]=min(tree[i],jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

int ans[MAXN];
void down(int l,int r,int i){
    if(l==r){
        ans[l]=tree[i];
    }
    else{
        int mid=(l+r)>>1;
        tree[i<<1]=min(tree[i<<1],tree[i]);
        tree[i<<1|1]=min(tree[i<<1|1],tree[i]);
        down(l,mid,i<<1);
        down(mid+1,r,i<<1|1);
    }
}

void bfs_lt() {
    queue<int> q;
    // 初始化：主路径上的每个节点都与自身连接
    for(int i = 1; i <= tot; i++) {
        q.push(path[i]);
        lt[path[i]] = i;  // 主路径上的节点，lt就是它们自己的位置
    }
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            // 关键条件：v不在主路径上，且v的lt还未设置，且(u,v)在最短路径树上
            if(id[v] == 0 && lt[v] == 0 && dis1[u] + w == dis1[v]) {
                lt[v] = lt[u];  // v继承u的连接位置
                q.push(v);
            }
        }
    }
}

void bfs_rt() {
    queue<int> q;
    // 初始化：主路径上的每个节点都与自身连接
    for(int i = tot; i >= 1; i--) {
        q.push(path[i]);
        rt[path[i]] = i;  // 主路径上的节点，rt就是它们自己的位置
    }
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            // 关键条件：v不在主路径上，且v的rt还未设置，且(u,v)在最短路径树上
            if(id[v] == 0 && rt[v] == 0 && dis2[u] + w == dis2[v]) {
                rt[v] = rt[u];  // v继承u的连接位置
                q.push(v);
            }
        }
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(dis1,1);
    dijkstra(dis2,n);
    getpath();

    bfs_lt();
    bfs_rt();

    build(1,tot,1);
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(!inpath[i]&&lt[u]>0&&rt[v]>0&&lt[u]<rt[v]){
                update(lt[u],rt[v]-1,dis1[u]+dis2[v]+w,1,tot,1);
            }
        }
    }
    down(1,tot,1);
    int cnt=0,res=0;
    for(int i=1;i<tot;i++){
        if(ans[i]>res){
            res=ans[i];
            cnt=1;
        }
        else if(ans[i]==res){
            cnt++;
        }
    }
    if(res==dis1[n]){
        cnt=m;
    }
    cout<<res<<' '<<cnt<<endl;
    return 0;
}