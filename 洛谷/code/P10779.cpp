#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 4e5+5;
const int INF = 1e9;

int n,m;
int val[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=2;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;

int cycle[MAXN];
int dp[MAXN][2];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dponcycle(int  u,int v){
    int sz=0;
    int pop;
    do{
        pop=sta[top--];
        cycle[++sz]=pop;
    }while(pop!=v);
    // 不选u的情况
    int pre0=dp[cycle[1]][0];
    int pre1=dp[cycle[1]][1];
    int cur0,cur1;
    for(int i=2;i<=sz;i++){
        int x=cycle[i];
        cur0=max(pre0,pre1)+dp[x][0];
        cur1=pre0+dp[x][1];
        pre0=cur0;
        pre1=cur1;
    }
    dp[u][0]+=max(pre0,pre1);
    // 选择u的情况
    pre0=dp[cycle[1]][0];
    pre1=-INF;
    for(int i=2;i<=sz;i++){
        int x=cycle[i];
        cur0=max(pre0,pre1)+dp[x][0];
        cur1=pre0+dp[x][1];
        pre0=cur0;
        pre1=cur1;
    }
    dp[u][1]+=pre0;
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    dp[u][0]=0;
    dp[u][1]=val[u];

    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }

        int v=to[i];
        if(dfn[v]==0){
            tarjan(v,i);
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
            }
            else if(low[v]>dfn[u]){
                dp[u][0]+=max(dp[v][0],dp[v][1]);
                dp[u][1]+=dp[v][0];
                top--;
            }
            else{
                dponcycle(u,v);
            }
        }
        else if(dfn[v]<dfn[u]){
            low[u]=min(low[u],dfn[v]);
        }
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
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        val[i]=1;
    }

    tarjan(1,0);
    cout<<max(dp[1][0],dp[1][1])<<endl;
    return 0;
}