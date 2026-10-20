#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e4+5;
const int MAXM = MAXN*4;
const int MAXQ = 1e5+5;
const int INF = 1e16;

int n,m,q;
int px[MAXN];
int py[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cntg=1;

int dis[MAXN];
int tag[MAXN];
int tim;

struct node{
    int x1,y1,x2,y2;
    int u,v;
};
node nums[MAXQ];
int ans[MAXQ];

struct cmp{
    bool operator()(pair<int,int> a,pair<int,int>b){
        return a.first>b.first;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

int id(int x,int y){
    return (x-1)*m+y;
}

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dijkstra(int xl,int xr,int yl,int yr,int s){
    ++tim;
    while(!heap.empty()){
        heap.pop();
    }

    tag[s]=tim;
    dis[s]=0;
    heap.push({0,s});
    while(!heap.empty()){
        pair<int,int>tmp=heap.top();
        heap.pop();

        int d=tmp.first;
        int u=tmp.second;

        if(d!=dis[u]){
            continue;
        }

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(px[v]<xl||px[v]>xr||py[v]<yl||py[v]>yr){
                continue;
            }
            int nd=d+weight[i];
            if(tag[v]!=tim||nd<dis[v]){
                tag[v]=tim;
                dis[v]=nd;
                heap.push({nd,v});
            }
        }
    }
}

void solve(int xl,int xr,int yl,int yr,const vector<int>& ids){
    int len=ids.size();
    if(len==0){
        return ;
    }

    if(xl==xr&&yl==yr){
        for(auto k:ids){
            ans[k]=0;
        }
        return ;
    }

    vector<int>lt,rt;
    lt.reserve(len);
    rt.reserve(len);

    if(xr-xl>=yr-yl){
        int mid=(xr+xl)>>1;
        for(int y=yl;y<=yr;y++){
            int s=id(mid,y);
            dijkstra(xl,xr,yl,yr,s);

            for(auto k:ids){
                int u=nums[k].u;
                int v=nums[k].v;
                ans[k]=min(ans[k],dis[u]+dis[v]);
            }
        }
        for(auto k:ids){
            if(nums[k].x1<mid&&nums[k].x2<mid){
                lt.push_back(k);
            }
            if(nums[k].x1>mid&&nums[k].x2>mid){
                rt.push_back(k);
            }
        }

        if(xl<mid){
            solve(xl,mid-1,yl,yr,lt);
        }
        if(xr>mid){
            solve(mid+1,xr,yl,yr,rt);
        }
    }
    else{
        int mid=(yr+yl)>>1;
        for(int x=xl;x<=xr;x++){
            int s=id(x,mid);
            dijkstra(xl,xr,yl,yr,s);

            for(auto k:ids){
                int u=nums[k].u;
                int v=nums[k].v;
                ans[k]=min(ans[k],dis[u]+dis[v]);
            }
        }
        for(auto k:ids){
            if(nums[k].y1<mid&&nums[k].y2<mid){
                lt.push_back(k);
            }
            if(nums[k].y1>mid&&nums[k].y2>mid){
                rt.push_back(k);
            }
        }

        if(yl<mid){
            solve(xl,xr,yl,mid-1,lt);
        }
        if(yr>mid){
            solve(xl,xr,mid+1,yr,rt);
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int u=id(i,j);
            px[u]=i,py[u]=j;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int w;
            cin>>w;
            int u=id(i,j);
            int v=id(i,j+1);
            addedge(u,v,w);
            addedge(v,u,w);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int w;
            cin>>w;
            int u=id(i,j);
            int v=id(i+1,j);
            addedge(u,v,w);
            addedge(v,u,w);
        }
    }

    cin>>q;
    vector<int>ids;
    ids.reserve(q);
    for(int i=1;i<=q;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        nums[i]={x1,y1,x2,y2,id(x1,y1),id(x2,y2)};
        ans[i]=INF;
        ids.push_back(i);
    }

    solve(1,n,1,m,ids);

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}