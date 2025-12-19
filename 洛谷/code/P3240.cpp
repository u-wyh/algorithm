#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 105;

int n,m;
int comb[MAXN][MAXN];
int fa[MAXN];
struct node{
    int u,v;
};
int len=0;
node nums[MAXN];
int g[MAXN];
int in[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int sz[MAXN];
int f[MAXN][MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    sz[u]=1;
    f[u][1]=1;
    for(int ei=head[u];ei;ei=nxt[ei]){
        int v=to[ei];

        dfs(v);
        for(int i=1;i<=n;i++){
            g[i]=0;
        }
        for(int i=1;i<=sz[u]+sz[v];i++){
            for(int j=1;j<=sz[u];j++){
                for(int k=1;k<=sz[v];k++){
                    if(k-i+j<0){
                        continue;
                    }
                    g[i]=(g[i]+(((f[u][j]*f[v][k])%MOD)*((comb[i-1][j-1]*comb[j-1][k-i+j])%MOD)%MOD))%MOD;
                }
            }
        }
        for(int i=1;i<=sz[u]+sz[v];i++){
            f[u][i]=g[i];
        }
        sz[u]+=sz[v];
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        char c;
        cin>>u>>c>>v;
        if(c=='='){
            un(u,v);
        }
        else{
            nums[++len]={u,v};
        }
    }
    for(int i=1;i<=len;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        in[fy]++;
        addedge(fx,fy);
    }
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(i==find(i)&&in[i]==0){
            q.push(i);
            addedge(n+1,i);
        }
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(--in[v]==0){
                q.push(v);
            }
        }
    }
    bool flag=false;
    for(int i=1;i<=n;i++){
        if(in[i]){
            flag=true;
            break;
        }
    }
    if(flag){
        cout<<0<<endl;
        return 0;
    }

    dfs(n+1);
    int ans=0;
    for(int i=1;i<=sz[n+1];i++){
        ans=(ans+f[n+1][i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}