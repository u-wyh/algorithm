#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1030;
const int MAXH = 15;

int n,m;
int f[MAXN][MAXH];
int g[MAXN][MAXH];
int dp[MAXN][MAXN];
int vis[MAXH];

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

void dfs(int u,int d){
    for(int i=0;i<=(1<<d);i++){
        dp[u][i]=0;
    }

    if(d==0){
        for(int i=1;i<=n;i++){
            if(vis[i]){
                dp[u][1]+=f[u][i];
            }
            else{
                dp[u][0]+=g[u][i];
            }
        }
    }
    else{
        int lt=u<<1;
        int rt=u<<1|1;

        vis[d]=0;
        dfs(lt,d-1);
        dfs(rt,d-1);

        for(int i=0;i<=(1<<(d-1));i++){
            for(int j=0;j<=(1<<(d-1));j++){
                dp[u][i+j]=max(dp[u][i+j],dp[lt][i]+dp[rt][j]);
            }
        }

        vis[d]=1;
        dfs(lt,d-1);
        dfs(rt,d-1);

        for(int i=0;i<=(1<<(d-1));i++){
            for(int j=0;j<=(1<<(d-1));j++){
                dp[u][i+j]=max(dp[u][i+j],dp[lt][i]+dp[rt][j]);
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    n--;

    int offset=1<<n;
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++){
            f[i+offset][j]=read();
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++){
            g[i+offset][j]=read();
        }
    }

    dfs(1,n);
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,dp[1][i]);
    }
    cout<<ans<<endl;
    return 0;
}