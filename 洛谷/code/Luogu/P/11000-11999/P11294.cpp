#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int ans;
int ans2;

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int tree[MAXN];
int dp[MAXN];

int dep[MAXN];

int tmp1[MAXN];
int tmp2[MAXN];

bool vis[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    int ans1=0,ans2=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        if(dp[v]>=ans1){
            ans2=ans1;
            ans1=dp[v];
        }
        else if(dp[v]>ans2){
            ans2=tree[v];
        }
    }
    dp[u]=1+ans1;
    tree[u]=1+ans1+ans2;
    tmp1[u]=ans1;
    tmp2[u]=ans2;
    // cout<<u<<": "<<dp[u]<<' '<<tree[u]<<endl;
}

void dfs1(int u,int fa,bool flag){
    if(flag||tree[u]==ans){
        flag=1;
    }
    int v1=0,v2=0;
    vis[u]=flag;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        if(v1==0&&tmp1[u]==dp[v]){
            dfs1(v,u,flag);
            v1=v;
        }
        else if(v2==0&&tmp2[u]==dp[v]){
            dfs1(v,u,flag);
            v2=v;
        }
    }
}

void dfs2(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
    }
    ans2=max(ans2,dep[u]);
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        ans=max(ans,tree[i]);
    }
    dfs1(1,0,0);
    // cout<<777<<endl;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            continue;
        }
        for(int j=head[i];j;j=nxt[j]){
            int v=to[j];
            if(!vis[v])
                dfs2(v,i);
        }
    }
    // cout<<ans<<' '<<ans2<<endl;
    ans+=ans2;
    if(ans==n){
        cout<<(n-1);
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}