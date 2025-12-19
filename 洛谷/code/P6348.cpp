#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e5+5;
const int MAXT = 5e6+5;
const int MAXE = 3e7+5;
const int INF = 1e9;

int n,m,st;

int dis[MAXT];
bool vis[MAXT];
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

int nodecnt;
int root1,root2;
int ls1[MAXN<<2];
int rs1[MAXN<<2];
int ls2[MAXN<<2];
int rs2[MAXN<<2];

int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cnt=1;

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

int build1(int l,int r){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int now=++nodecnt;
        ls1[now]=build1(l,mid);
        rs1[now]=build1(mid+1,r);
        addedge(now,ls1[now],0);
        addedge(now,rs1[now],0);
        return now;
    }
}

int build2(int l,int r){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int now=++nodecnt;
        ls2[now]=build2(l,mid);
        rs2[now]=build2(mid+1,r);
        addedge(ls2[now],now,0);
        addedge(rs2[now],now,0);
        return now;
    }
}

void update1(int jobl,int jobr,int jobv,int jobw,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(jobv,i,jobw);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update1(jobl,jobr,jobv,jobw,l,mid,ls1[i]);
        }
        if(jobr>mid){
            update1(jobl,jobr,jobv,jobw,mid+1,r,rs1[i]);
        }
    }
}

void update2(int jobl,int jobr,int jobv,int jobw,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv,jobw);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update2(jobl,jobr,jobv,jobw,l,mid,ls2[i]);
        }
        if(jobr>mid){
            update2(jobl,jobr,jobv,jobw,mid+1,r,rs2[i]);
        }
    }
}

void dijkstra(){
    for(int i=1;i<=nodecnt;i++){
        dis[i]=INF;
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
}

int main()
{
    n=read(),m=read(),st=read();
    nodecnt=n;

    root1=build1(1,n);
    root2=build2(1,n);
    while(m--){
        int a,b,c,d;
        a=read(),b=read(),c=read(),d=read();
        int x = ++nodecnt;
        update1(a,b,x,1,1,n,root1);
        update2(c,d,x,0,1,n,root2);
        int y = ++nodecnt;
        update1(c,d,y,1,1,n,root1);
        update2(a,b,y,0,1,n,root2);
    }
    dijkstra();
    for(int i=1;i<=n;i++){
        printf("%d\n",dis[i]);
    }
    return 0;
}