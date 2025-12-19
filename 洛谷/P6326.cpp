#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 4005;

int n,m;
int v[MAXN];
int c[MAXN];
int d[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

int dp[MAXN][MAXM];

int seg[MAXN];
int low[MAXN];
int dfncnt;

int val[MAXN];
int cost[MAXN];

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

void prepare(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        vis[i]=false;
    }
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]&&v!=fa){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!vis[v]&&v!=fa&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa){
    seg[++dfncnt]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]&&v!=fa){
            dfs(v,u);
        }
    }
    low[u]=dfncnt;
}

int calc(int u){
    dfncnt=0;
    dfs(u,0);
    for(int i=dfncnt;i>=1;i--){
        int cur=seg[i];
        int cnt=d[cur]-1;
        int num=0;
        for(int k=1;k<=cnt;k<<=1){
            val[++num]=v[cur]*k;
            cost[num]=c[cur]*k;
            cnt-=k;
        }
        if(cnt>0){
            val[++num]=v[cur]*cnt;
            cost[num]=c[cur]*cnt;
        }

        for(int j=m;j>=c[cur];j--){
            dp[i][j]=dp[i+1][j-c[cur]]+v[cur];
        }
        for(int k=1;k<=num;k++){
            for(int j=m;j>=cost[k];j--){
                dp[i][j]=max(dp[i][j],dp[i][j-cost[k]]+val[k]);
            }
        }
        for(int j=0;j<=m;j++){
            dp[i][j]=max(dp[i][j],dp[low[cur]+1][j]);
        }
    }
    int ans=dp[1][m];
    for(int i=1;i<=dfncnt;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=0;
        }
    }
    return ans;
}

int solve(int u){
    vis[u]=true;
    int ans=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans=max(ans,solve(getcentroid(v,u)));
        }
    }
    return ans;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            v[i]=read();
        }
        for(int i=1;i<=n;i++){
            c[i]=read();
        }
        for(int i=1;i<=n;i++){
            d[i]=read();
        }
        prepare();
        for(int i=1;i<n;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            addedge(v,u);
        }
        cout<<solve(getcentroid(1,0))<<endl;
    }
    return 0;
}