#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXV = 105;
const int MAXE = 4*MAXN*MAXN;
const int INF = 1e9;
const double eps = 1e-8;

int n,m,s,t;
double all;
int a[MAXN],b[MAXN];
int node[MAXN];

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
double now[MAXE];
double cap[MAXE];

void addedge(int u,int v,double w){
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
            double w=cap[i];
            double k=now[i];
            if(dep[v]<0&&(k+eps<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

double dfs(int u,double f){
    if(u==t){
        return f;
    }
    double flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        double w=cap[i];
        double k=now[i];
        if(dep[u]+1==dep[v]&&k+eps<w){
            double d=dfs(v,min(f,w-k));
            if(d>eps){
                now[i]+=d;
                now[i^1]-=d;
                flow+=d;
                f-=d;
                if(f<=eps){
                    break;
                }
            }
        }
    }
    return flow;
}

double maxflow(){
    double flow=0;
    while(bfs()){
        //当前弧全部初始化为最初值
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        double maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

bool check(double limit){
    for(int i=2;i<=cnt;i++){
        now[i]=0;
    }
    for(int i=1;i<=m;i++){
        cap[node[i]]=limit*b[i];
    }
    double flow=maxflow();
    return flow+eps>=all;
}

int main()
{
    cin>>n>>m;
    all=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        all+=a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    s=n+m+1,t=s+1;
    for(int i=1;i<=n;i++){
        addedge(i,t,a[i]);
    }
    for(int i=1;i<=m;i++){
        addedge(s,i+n,0);
        node[i]=cnt-2;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            int op;
            cin>>op;
            if(op){
                addedge(i+n,j,INF);
            }
        }
    }

    int need=100;
    double l=0,r=1e8,ans=0;
    while(need--){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid;
        }
        else{
            l=mid;
        }
    }
    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}