#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 2e4+5;
const double eps = 1e-8;
const double INF = 1e18;

int n,s,t;
int a[MAXN][MAXN];
int b[MAXN][MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cap[MAXM];
double cost[MAXM];
int cnt = 2;

double dis[MAXN];
int pre[MAXN];
int preedge[MAXN];
int flow[MAXN];
bool in[MAXN];

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

inline void addedge(int u, int v, int w, double c) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    cap[cnt] = w;
    cost[cnt] = c;
    head[u] = cnt++;

    nxt[cnt] = head[v];
    to[cnt] = u;
    cap[cnt] = 0;
    cost[cnt] = -c;
    head[v] = cnt++;
}

bool spfa(){
    for(int i=1;i<=t;i++){
        dis[i]=INF;
        in[i]=false;
        flow[i]=0;
    }

    queue<int>q;
    q.push(s);
    dis[s]=0;
    in[s]=true;
    flow[s]=1e9;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(cap[i]>0&&dis[v]>dis[u]+cost[i]){
                dis[v]=dis[u]+cost[i];
                pre[v]=u;
                preedge[v]=i;
                flow[v]=min(flow[u],cap[i]);
                if(!in[v]){
                    in[v]=true;
                    q.push(v);
                }
            }
        }
    }

    return dis[t]<INF;
}

double mincostmaxflow(){
    double mincost=0;
    while(spfa()){
        int f=flow[t];
        mincost+=f*dis[t];
        int cur=t;
        while(cur!=s){
            int edge=preedge[cur];
            cap[edge]-=f;
            cap[edge^1]+=f;
            cur=pre[cur];
        }
    }
    return mincost;
}

bool check(double mid){
    for(int i=1;i<=2*n+2;i++){
        head[i]=0;
    }
    cnt=2;

    s=2*n+1;
    t=2*n+2;

    for(int i=1;i<=n;i++){
        addedge(s,i,1,0);
    }
    for(int i=1;i<=n;i++){
        addedge(i+n,t,1,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            double cost=mid*b[i][j]-a[i][j];
            addedge(i,n+j,1,cost);
        }
    }

    double mincost=mincostmaxflow();
    return mincost<=0;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=read();
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            b[i][j]=read();
        }
    }

    double l=0,r=10000,ans=0;
    while(r-l>=eps){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid;
        }
        else{
            r=mid;
        }
    }
    printf("%.6lf\n",ans);
    return 0;
}