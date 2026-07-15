#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
const int MAXN = 105;
const int MAXM = 1005;
const int MAXV = 105;
const int MAXE = MAXM*2;
const int INF = 1e9;

int n,m,p,s,t;
double total;

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
double now[MAXE];
double cap[MAXE];
double origin[MAXE];

void addedge(int u,int v,double w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    origin[cnt]=w;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    origin[cnt]=0;
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
                now[i^1]-=d;//更新反向边
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
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        double maxflow;
        while((maxflow=dfs(s,INF))>eps){
            flow+=maxflow;
        }
    }
    return flow;
}

bool check(double limit){
    for(int i=2;i<=cnt;i++){
        cap[i]=min(origin[i],limit);
        now[i]=0;
    }
    return maxflow()+eps>=total;
}

int main()
{
    cin>>n>>m>>p;
    s=1,t=n;
    double lt=0,rt=0,ans=0;
    for(int i=1;i<=m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        rt=max(rt,w);
        addedge(u,v,w);
    }

    total=maxflow();
    cout << fixed << setprecision(0) << total << endl;

    int need=50;
    while(need--){
        double mid=(lt+rt)/2;
        if(check(mid)){
            ans=mid;
            rt=mid;
        }
        else{
            lt=mid;
        }
    }

    double cost=ans*p;
    cout << fixed << setprecision(4) << cost << endl;

    return 0;
}