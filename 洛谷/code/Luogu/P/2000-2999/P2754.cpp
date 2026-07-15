#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int MAXM = 25;
const int MAXV = 1005*MAXN;
const int MAXE = 20*MAXV;
const int INF = 1e9;

int n,m,k,s,t;
int shipcap[MAXM];
int route[MAXN][MAXN];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

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
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    for(int i=1;i<=t;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

int maxflow(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

int id(int t,int x){
    if(x==0){
        x=n+1;
    }
    else if(x==-1){
        x=n+2;
    }
    return t*(n+2)+x;
}

bool check(int limit){
    cnt=2;
    s=id(0,0),t=id(limit,n+2);
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
    for(int i=0;i<limit;i++){
        for(int j=-1;j<=n;j++){
            int u=id(i,j);
            int v=id(i+1,j);
            addedge(u,v,INF);
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<limit;j++){
            int from=route[i][(j%route[i][0])+1];
            int to=route[i][((j+1)%route[i][0])+1];
            int u=id(j,from);
            int v=id(j+1,to);
            addedge(u,v,shipcap[i]);
        }
    }
    int flow=maxflow();
    return flow>=k;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        shipcap[i]=read();
        route[i][0]=read();
        for(int j=1;j<=route[i][0];j++){
            route[i][j]=read();
        }
    }
    int l=0,r=1000,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    if(ans==-1){
        cout<<0<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}