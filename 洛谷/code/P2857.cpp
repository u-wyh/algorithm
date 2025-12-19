#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 25;
const int MAXT = 2005;
const int MAXE = 6e4+5;
const int INF = 1e9;

int n,m,s,t;
int val[MAXN][MAXM];
int capacity[MAXM];

int dep[MAXT];
int iter[MAXT];

int cnt=2;
int head[MAXT];
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
    for(int i=1;i<=n+m+2;i++){
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
                now[i^1]-=d;//更新反向边
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
        for(int i=1;i<=n+m+2;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

bool check(int len){
    for(int l=1;l+len-1<=m;l++){
        int r=l+len-1;

        for(int i=1;i<=t;i++){
            head[i]=0;
        }
        cnt=2;

        for(int i=1;i<=n;i++){
            addedge(s,i,1);
        }
        for(int i=1;i<=n;i++){
            for(int j=l;j<=r;j++){
                addedge(i,n+val[i][j],1);
            }
        }
        for(int i=1;i<=m;i++){
            addedge(n+i,t,capacity[i]);
        }
        if(maxflow()==n){
            return true;
        }
    }
    return false;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            val[i][j]=read();
        }
    }
    for(int i=1;i<=m;i++){
        capacity[i]=read();
    }
    s=n+m+1,t=n+m+2;
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
    return 0;
}