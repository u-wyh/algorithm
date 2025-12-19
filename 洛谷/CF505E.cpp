#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9;

int n,m;

bool vis[MAXN];
int dis[MAXN];
int change[MAXN];
int pre[MAXN];

struct edge{
    int u,v,w;
    bool flag;
}nums[MAXN];

struct node{
    int u,dis,change;
};

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int id[MAXN<<1];
int cnt=1;

struct compare{
    bool operator()(const node&a,const node&b){
        if(a.dis==b.dis){
            return a.change>b.change;
        }
        else{
            return a.dis>b.dis;
        }
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

void dijkstra(){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        change[i]=INF;
    }
    dis[1]=0;
    change[1]=0;
    heap.push({1,0,0});
    while(!heap.empty()){
        int u=heap.top().u;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        if(u==n){
            break;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dis[v]>dis[u]+1){
                dis[v]=1+dis[u];
                pre[v]=(i+1)/2;
                change[v]=change[u]+(1-weight[i]);
                heap.push({v,dis[v],change[v]});
            }
            else if(dis[v]==dis[u]+1&&change[v]>(change[u]+(1-weight[i]))){
                pre[v]=(i+1)/2;
                change[v]=change[u]+(1-weight[i]);
                heap.push({v,dis[v],change[v]});
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    int ans=0;
    for(int i=1;i<=m;i++){
        nums[i].u=read();
        nums[i].v=read();
        nums[i].w=read();
        ans+=nums[i].w;
        addedge(nums[i].u,nums[i].v,nums[i].w);
        addedge(nums[i].v,nums[i].u,nums[i].w);
    }
    dijkstra();
    printf("%d\n",ans-dis[n]+2*change[n]);
    int i=n;
    while(1){
        nums[pre[i]].flag=true;
        i=(nums[pre[i]].u+nums[pre[i]].v)-i;
        if(i==1){
            break;
        }
    }
    for(int i=1;i<=m;i++){
        if(nums[i].flag){
            if(nums[i].w!=1){
                printf("%d %d 1\n",nums[i].u,nums[i].v);
            }
        }
        else{
            if(nums[i].w!=0){
                printf("%d %d 0\n",nums[i].u,nums[i].v);
            }
        }
    }
    return 0;
}