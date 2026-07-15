#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

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
int height[MAXN];

int premax[MAXN];
int prediameter[MAXN];

int sufmax[MAXN];
int sufdiameter[MAXN];

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

int dponcycle(){
    int best=0;
    int sum=0;
    for(int i=1;i<=cnta;i++){
        premax[i]=max(premax[i-1],height[i]+sum);
        prediameter[i]=max(prediameter[i-1],sum+height[i]+best);
        best=max(best,height[i]-sum);
        sum+=val[i];
    }

    sufmax[cnta]=height[cnta]+val[cnta];
    sufdiameter[cnta]=height[cnta];
    best=height[cnta]-val[cnta];
    sum=val[cnta]+val[cnta-1];
    for(int i=cnta-1;i>=1;i--){
        sufmax[i]=max(sufmax[i+1],height[i]+sum);
        sufdiameter[i]=max(sufdiameter[i+1],sum+height[i]+best);
        best=max(best,height[i]-sum);
        sum+=val[i-1];
    }

    int ans=LLONG_MAX;
    for(int i=1;i<cnta;i++){
        ans=min(ans,max(premax[i]+sufmax[i+1],max(prediameter[i],sufdiameter[i+1])));
    }
    ans=min(ans,prediameter[cnta]);
    return ans;
}

int compute(){
    dfs(1);
    int ans1=0;
    for(int i=1;i<=cnta;i++){
        diameter=0;
        dpontree(arr[i],0);
        ans1=max(ans1,diameter);
        height[i]=dist[arr[i]];
    }
    int ans2=dponcycle();
    return max(ans1,ans2);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    printf("%.1lf",compute()/2.0);
    return 0;
}