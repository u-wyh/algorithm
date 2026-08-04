#include<bits/stdc++.h>
using namespace std;
const int MAXV = 2e4+5;
const int MAXT = 1e5+5;
const int MAXE = 25e4+5;
const int INF = 1e9;

int n,m,t;
int s,tar,tot;

int ex[MAXT];
int ey[MAXT];
int eid[MAXT];

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int cntg=2;

int dep[MAXV];
int cur[MAXV];
int que[MAXV];

int dfn[MAXV];
int low[MAXV];
int dfncnt;

int sta[MAXV];
int top;

int belong[MAXV];
int sccCnt;

int ans[MAXT];
int cntans;

inline int addedge(int u,int v,int w){
    int id=cntg;

    nxt[cntg]=head[u];
    to[cntg]=v;
    cap[cntg]=w;
    head[u]=cntg++;

    nxt[cntg]=head[v];
    to[cntg]=u;
    cap[cntg]=0;
    head[v]=cntg++;

    return id;
}

bool bfs(){
    for(int i=0;i<tot;i++){
        dep[i]=-1;
    }

    int l=1,r=0;
    que[++r]=s;
    dep[s]=0;

    while(l<=r){
        int u=que[l++];

        for(int i=head[u];i;i=nxt[i]){
            if(cap[i]==0){
                continue;
            }

            int v=to[i];

            if(dep[v]!=-1){
                continue;
            }

            dep[v]=dep[u]+1;
            que[++r]=v;
        }
    }

    return dep[tar]!=-1;
}

int dfs(int u,int flow){
    if(u==tar){
        return flow;
    }

    int used=0;

    for(int &i=cur[u];i;i=nxt[i]){
        if(cap[i]==0){
            continue;
        }

        int v=to[i];

        if(dep[v]!=dep[u]+1){
            continue;
        }

        int ret=dfs(v,min(flow-used,cap[i]));

        if(ret==0){
            continue;
        }

        cap[i]-=ret;
        cap[i^1]+=ret;
        used+=ret;

        if(used==flow){
            break;
        }
    }

    return used;
}

void dinic(){
    while(bfs()){
        for(int i=0;i<tot;i++){
            cur[i]=head[i];
        }

        while(dfs(s,INF)){
        }
    }
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;

    for(int i=head[u];i;i=nxt[i]){
        if(cap[i]==0){
            continue;
        }

        int v=to[i];

        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(belong[v]==0){
            low[u]=min(low[u],dfn[v]);
        }
    }

    if(low[u]==dfn[u]){
        sccCnt++;

        while(1){
            int v=sta[top--];
            belong[v]=sccCnt;

            if(v==u){
                break;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>t;

    s=0;
    tar=n+m+1;
    tot=tar+1;

    for(int i=1;i<=n;i++){
        addedge(s,i,1);
    }

    for(int i=1;i<=t;i++){
        cin>>ex[i]>>ey[i];

        int u=ex[i];
        int v=n+ey[i];

        eid[i]=addedge(u,v,1);
    }

    for(int i=1;i<=m;i++){
        addedge(n+i,tar,1);
    }

    dinic();

    for(int i=0;i<tot;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }

    for(int i=1;i<=t;i++){
        int u=ex[i];
        int v=n+ey[i];

        // cap[eid[i]]==0，说明这条边在当前最大匹配中
        if(cap[eid[i]]==0){
            continue;
        }

        // 位于同一个残量环中，可以出现在另一个最大匹配中
        if(belong[u]==belong[v]){
            continue;
        }

        ans[++cntans]=i;
    }

    cout<<cntans<<"\n";

    for(int i=1;i<=cntans;i++){
        cout<<ans[i];

        if(i<cntans){
            cout<<" ";
        }
    }

    cout<<"\n";

    return 0;
}