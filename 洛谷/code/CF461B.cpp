#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 1e9+7;

int n;
int val[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

long long dp[MAXN][2];

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dp[u][val[u]]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        dp[u][1]=(dp[u][1]*dp[v][0]+dp[u][1]*dp[v][1]+dp[u][0]*dp[v][1])%MOD;
        dp[u][0]=(dp[u][0]*dp[v][0]+dp[u][0]*dp[v][1])%MOD;
    }
}

int main()
{
    n=read();
    for(int i=2;i<=n;i++){
        int u;
        u=read();
        u++;
        addedge(u,i);
        addedge(i,u);
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    dfs(1,0);
    printf("%lld",dp[1][1]);
    return 0;
}