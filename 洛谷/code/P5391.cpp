#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXH = 20;

int n,m;

int cnt;
int cost[MAXN];
int val[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int sta[MAXN];
int top;

bool vis[MAXN];
int sz[MAXN];
int son[MAXN];

int dp[MAXH][MAXN];

int ans[MAXN];
int id[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u){
    vis[u]=true;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int now,int last){
    for(int i=0;i<=m;i++){
        dp[now][i]=dp[last][i];
        if(i>=cost[u]){
            dp[now][i]=max(dp[now][i],dp[now][i-cost[u]]+val[u]);
        }
        ans[u]=max(ans[u],dp[now][i]);
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,now+1,now);
        }
    }

    if(son[u]){
        dfs2(son[u],now,now);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string op;
        cin>>op;
        if(op[0]=='a'){
            ++cnt;
            if(top){
                addedge(sta[top],cnt);
            }
            cin>>cost[cnt]>>val[cnt];
            sta[++top]=cnt;
        }
        else{
            top--;
        }
        id[i]=sta[top];
    }

    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs1(i);
            dfs2(i,1,0);
        }
    }

    for(int i=1;i<=n;i++){
        printf("%d\n",ans[id[i]]);
    }
    return 0;
}