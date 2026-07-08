#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];

int x,y,skipedge;
int dp[MAXN][2];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            dfs(v);
        }
        else if(dfn[u]<dfn[v]){
            x=u,y=v;
            skipedge=(i+1)>>1;
        }
    }
}

void dponcycle(int u,int fa){
    dp[u][0]=0;
    dp[u][1]=val[u];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(((i+1)>>1)==skipedge||v==fa){
            continue;
        }
        dponcycle(v,u);
        dp[u][0]+=max(dp[v][0],dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
}

int compute(){
    int ans=0;
    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            x=y=0;
            dfs(i);
            dponcycle(x,0);
            int cur=dp[x][0];
            dponcycle(y,0);
            cur=max(cur,dp[y][0]);
            ans+=cur;
        }
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>val[i]>>x;
        addedge(x,i);
        addedge(i,x);
    }
    cout<<compute()<<endl;
    return 0;
}