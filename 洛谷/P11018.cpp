#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e9;

int n;
int col[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

int dp[MAXN][2][2];
int f[MAXN][2][2];

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
    int flag=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        flag++;
        for(int a=0;a<2;a++){
            for(int b=0;b<2;b++){
                f[u][a][b]=INF;
            }
        }
        if(flag==1){
            f[u][0][1]=dp[v][0][1];
            f[u][1][1]=dp[v][1][1];
            f[u][1][0]=dp[v][1][0];
            f[u][0][0]=dp[v][0][0];
        }
        else{
            for(int a=0;a<2;a++){
                for(int b=0;b<2;b++){
                    for(int c=0;c<2;c++){
                        f[u][a][b^c]=min(f[u][a][b^c],dp[u][a][b]+dp[v][a][c]);
                    }
                }
            }
        }
        for(int a=0;a<2;a++){
            for(int b=0;b<2;b++){
                dp[u][a][b]=f[u][a][b];
            }
        }
    }
    if(flag==0){
        dp[u][col[u]][0]=0;
        dp[u][col[u]^1][1]=1;
        dp[u][col[u]][1]=2;
        dp[u][col[u]^1][0]=1;
        return ;
    }
    dp[u][0][1]=dp[u][0][0]=dp[u][1][0]=dp[u][1][1]=INF;
    dp[u][col[u]][0]=min(f[u][col[u]][0],f[u][col[u]][1]+1);
    dp[u][col[u]^1][1]=min(f[u][col[u]^1][1],f[u][col[u]^1][0]+1);
    dp[u][col[u]][1]=dp[u][col[u]^1][1]+1;
    dp[u][col[u]^1][0]=dp[u][col[u]][0]+1;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        col[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    printf("%d\n",min(dp[1][1][0],dp[1][1][1]));
    return 0;
}