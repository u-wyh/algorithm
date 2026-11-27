// https://www.luogu.com.cn/problem/P3305
// 题意：输入点数 N、有向边数 M、总单位费用上限 P，源点为 1、汇点为 N，每条有向边 (A, B) 容量为 C（无自环）。
// Alice 先选定一个最大流方案，之后 Bob 为每条边分配总和为 P 的非负实数单位费用，总费用为各边实际流量×单位费用之和。
// Alice 希望总费用尽量小、Bob 希望总费用尽量大，双方均采取最优策略。
// 输出两行：第一行输出最大流整数，第二行输出最终总费用实数（建议四位以上小数）。
// 数据范围：N <= 100，M <= 1000，1 <= 每条边最大流量 C <= 50000，1 <= P <= 10。
#include<bits/stdc++.h>
// 算法标签：最大流、二分答案
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