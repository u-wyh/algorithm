#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAXN = 1e6+5;
const int MAXM = 5e6+5;

int n,m,k;
int dis[MAXN<<1];
bool vis[MAXN<<1];

int cnt=1;
int head[MAXN<<1];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

struct node{
    int id,x,y;
}nums[MAXN];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

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

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(){
    for(int i=0;i<=2*n+5;i++){
        dis[i]=INF;
    }
    dis[0]=0;
    heap.push({0,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        if(u==2*n+5){
            break;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

bool cmpx(node a,node b){
    return (a.x==b.x)?a.y<b.y:a.x<b.x;
}

bool cmpy(node a,node b){
    return (a.y==b.y)?a.x<b.x:a.y<b.y;
}

int main()
{
    n=read();
    nums[0].id=0,nums[0].x=read(),nums[0].y=read();
    addedge(0,1,0),addedge(0,2,0);
    addedge(1,2,1),addedge(2,1,1);
    nums[n+1].id=n+1,nums[n+1].x=read(),nums[n+1].y=read();
    addedge(2*n+3,2*n+5,0),addedge(2*n+4,2*n+5,0);
    addedge(2*n+3,2*n+4,1),addedge(2*n+4,2*n+3,1);
    for(int i=1;i<=n;i++){
        nums[i].id=i,nums[i].x=read(),nums[i].y=read();
        addedge(2*i+1,2*i+2,1);
        addedge(2*i+2,2*i+1,1);
    }
    sort(nums,nums+n+2,cmpx);
    for(int i=0;i<=n;i++){
        if(nums[i].x==nums[i+1].x){
            addedge(nums[i].id*2+1,nums[i+1].id*2+1,0);
            addedge(nums[i+1].id*2+1,nums[i].id*2+1,0);
        }
    }
    sort(nums,nums+n+2,cmpy);
    for(int i=0;i<=n;i++){
        if(nums[i].y==nums[i+1].y){
            addedge(nums[i].id*2+2,nums[i+1].id*2+2,0);
            addedge(nums[i+1].id*2+2,nums[i].id*2+2,0);
        }
    }
    dijkstra();
    if(dis[2*n+5]==INF){
        dis[2*n+5]=-1;
    }
    cout<<dis[2*n+5]<<endl;
    return 0;
}