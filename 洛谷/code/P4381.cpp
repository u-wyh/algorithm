#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];

int fromnode[MAXN];
int fromweight[MAXN];
bool cycle[MAXN];
int arr[MAXN];
int val[MAXN];
int cnta;

int dist[MAXN];
int diameter;
int sum[MAXN<<1];
int height[MAXN<<1];
int que[MAXN<<1];

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    for(int e=head[u];e;e=nxt[e]){
        int v=to[e];
        if(dfn[v]==0){
            fromnode[v]=u;
            fromweight[v]=weight[e];
            dfs(v);
        }
        else if(dfn[u]<dfn[v]) {
            cycle[u]=true;
            arr[++cnta]=u;
            val[cnta]=weight[e];
            for(int i=v;i!=u;i=fromnode[i]){
                cycle[i]=true;
                arr[++cnta]=i;
                val[cnta]=fromweight[i];
            }
        }
    }
}

void dpontree(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!cycle[v]){
            dpontree(v,u);
            diameter=max(diameter,dist[u]+dist[v]+w);
            dist[u]=max(dist[u],dist[v]+w);
        }
    }
}

int compute(int root){
    cnta=0;
    dfs(root);
    sum[1]=0;
    for(int i=2,j=1;j<=cnta;j++,i++){
        sum[i]=val[j];
    }
    for(int i=cnta+2;i<=2*cnta;i++){
        sum[i]=sum[i-cnta];
    }
    for(int i=1;i<=cnta*2;i++){
        sum[i]+=sum[i-1];
    }

    int ans1=0;
    for(int i=1;i<=cnta;i++){
        diameter=0;
        dpontree(arr[i],0);
        ans1=max(ans1,diameter);
        height[i]=dist[arr[i]];
        height[i+cnta]=dist[arr[i]];
    }

    int ans2=0;
    int ql=1,qr=0;
    for(int i=1;i<=cnta*2;i++){
        while(ql<=qr&&que[ql]<=i-cnta){
            ql++;
        }
        if(ql<=qr){
            ans2=max(ans2,height[i]+height[que[ql]]+sum[i]-sum[que[ql]]);
        }
        while(ql<=qr&&height[que[qr]]-sum[que[qr]]<=height[i]-sum[i]){
            qr--;
        }
        que[++qr]=i;
    }
    return max(ans1,ans2);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int u,w;
        cin>>u>>w;
        addedge(i,u,w);
        addedge(u,i,w);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            ans+=compute(i);
        }
    }
    cout<<ans<<endl;
    return 0;
}