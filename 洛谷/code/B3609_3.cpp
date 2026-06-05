#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int sta[MAXN];
int top;

int belong[MAXN];
int sccl[MAXN];
int sccr[MAXN];
int sccarr[MAXN];
int sccid[MAXN];
int scccnt;
int idx;

bool vis[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            if(belong[v]==0){
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u]) {
        scccnt++;
        sccl[scccnt] = idx + 1;
        int pop;
        do {
            pop = sta[top--];
            belong[pop] = scccnt;
            sccarr[++idx] = pop;
        } while (pop != u);
        sccr[scccnt] = idx;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
    }

    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }
    
    cout<<scccnt<<endl;
    for(int i=1;i<=n;i++){
        int b=belong[i];
        if(vis[b]){
            continue;
        }
        vis[b]=true;
        sort(sccarr+sccl[b],sccarr+sccr[b]+1);
        for(int j=sccl[b];j<=sccr[b];j++){
            cout<<sccarr[j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}