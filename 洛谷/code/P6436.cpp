#include<bits/stdc++.h>
using namespace std;

const int MAXN = 7505;
const int MAXM = 15005;
const long long INF = (1LL<<62);

int n,l,q;
long long t,d;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int wp[MAXM];
int we[MAXM];
int cntg=1;

long long disE[MAXN];
long long disP[MAXN];
long long need[MAXN];

long long best[MAXN];
long long dis[MAXN];

bool safe[MAXN];

long long ans[MAXN];
int cntans;

inline void addedge(int u,int v,int p,int e)
{
    nxt[cntg]=head[u];
    to[cntg]=v;
    wp[cntg]=p;
    we[cntg]=e;
    head[u]=cntg++;
}

// 预处理两人的根路径距离和背包需求
void dfs1(int u,int fa)
{
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v==fa){
            continue;
        }

        disE[v]=disE[u]+wp[i];
        disP[v]=disP[u]+we[i];
        need[v]=max(need[u],(long long)wp[i]);

        dfs1(v,u);
    }
}

// 枚举以s为一个端点的所有合法新增航线
void dfs2(int s,int u,int fa,int len,long long dist)
{
    if(u>s&&len>=q+1){
        long long w=dist/2;

        best[u]=min(best[u],disP[s]+w);
        best[s]=min(best[s],disP[u]+w);
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v==fa){
            continue;
        }

        long long nd=dist+we[i];

        if(nd>d){
            continue;
        }

        dfs2(s,v,u,len+1,nd);
    }
}

// 判断根路径上的所有点是否安全
void dfs3(int u,int fa)
{
    if(safe[u]){
        ans[++cntans]=need[u];
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v==fa){
            continue;
        }

        safe[v]=safe[u]&&disE[v]<=t+dis[v];
        dfs3(v,u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>t>>d>>l>>q;

    for(int i=1;i<n;i++){
        int u,v,p,e;
        cin>>u>>v>>p>>e;

        addedge(u,v,p,e);
        addedge(v,u,p,e);
    }

    dfs1(1,0);

    for(int i=1;i<=n;i++){
        best[i]=INF;
    }

    best[1]=0;

    for(int s=1;s<=n;s++){
        dfs2(s,s,0,0,0);
    }

    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > heap;

    for(int i=1;i<=n;i++){
        dis[i]=best[i];

        if(dis[i]<INF){
            heap.push({dis[i],i});
        }
    }

    while(!heap.empty()){
        long long du=heap.top().first;
        int u=heap.top().second;
        heap.pop();

        if(du!=dis[u]){
            continue;
        }

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            long long nd=du+we[i];

            if(nd<dis[v]){
                dis[v]=nd;
                heap.push({nd,v});
            }
        }
    }

    safe[1]=true;
    dfs3(1,0);

    if(cntans<l){
        cout<<"no solution\n";
        return 0;
    }

    sort(ans+1,ans+cntans+1);

    long long k=ans[l];
    int r=upper_bound(ans+1,ans+cntans+1,k)-ans-1;

    cout<<k<<'\n';
    cout<<r<<'\n';

    return 0;
}