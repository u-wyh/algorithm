#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXV = 2*MAXN;
const int MAXE = 10*MAXN;
const int INF = 1e9;

int n,m,s,t;
int node[MAXN];
int a[MAXN];
int b[MAXN];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

int edge[MAXN][2];

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
    return dep[t]>=0;
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

bool check(int limit){
    for(int i=2;i<=cnt;i++){
        now[i]=0;
    }
    for(int i=1;i<=n;i++){
        cap[node[i]]=limit;
    }
    int flow=maxflow();
    return flow==m;
}

int main()
{
    n=read(),m=read();
    s=n+m+1,t=s+1;
    for(int i=1;i<=n;i++){
        addedge(i,t,0);
        node[i]=cnt-2;
    }
    for(int i=1;i<=m;i++){
        a[i]=read(),b[i]=read();
        addedge(n+i,a[i],1);
        edge[i][0]=cnt-2;
        addedge(n+i,b[i],1);
        edge[i][1]=cnt-2;
    }
    for(int i=1;i<=m;i++){
        addedge(s,i+n,1);
    }
    int l=1,r=m,ans=0;
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
    cout<<ans<<endl;
    check(ans);
    for(int i=1;i<=m;i++){
        if(now[edge[i][0]]){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}