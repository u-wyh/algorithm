#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 1505;
const int MAXK = 3005;
const int MAXM = 1140000;

int n,tot;
int arr[MAXN][MAXN];

int fa[MAXK];
struct edge{
    int u,v,w;
}nums[MAXM];

int cntk=1;
int headk[MAXK];
int nxtk[MAXK];
int tok[MAXK];
int sz[MAXK];
int cnt[MAXK];
int ls[MAXK];
int rs[MAXK];
int cntu;

long long dp[MAXK][MAXN];

bool cmp(edge a,edge b){
    return a.w<b.w;
}

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

inline void addEdge(int u,int v){
    nxtk[cntk]=headk[u];
    tok[cntk]=v;
    headk[u]=cntk++;
}

inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void kruskalRebuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        cnt[i]=0;
        sz[i]=1;
    }
    cntu=n;
    for(int i=1;i<=tot;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            cntu++;
            fa[fx]=cntu;
            fa[fy]=cntu;
            fa[cntu]=cntu;
            if(sz[fx]<sz[fy])
                ls[cntu]=fx,rs[cntu]=fy;
            else
                ls[cntu]=fy,rs[cntu]=fx;
            sz[cntu]=sz[fx]+sz[fy];
            cnt[cntu]=cnt[fx]+cnt[fy]+1;
            addEdge(cntu,fx);
            addEdge(cntu,fy);
        }
        else{
            cnt[fx]++;
        }
    }
}

void dfs(int u){
    for(int i=headk[u];i;i=nxtk[i]){
        int v=tok[i];
        dfs(v);
    }
    if(sz[u]*(sz[u]-1)/2==cnt[u]){
        dp[u][1]=1;
    }
    for(int i=2;i<=sz[u];i++){
        for(int j=1;j<=min(i-1,sz[ls[u]]);j++){
            dp[u][i]=(dp[u][i]+dp[ls[u]][j]*dp[rs[u]][i-j])%MOD;
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            arr[i][j]=read();
            if(i<j){
                tot++;
                nums[tot].u=i,nums[tot].v=j,nums[tot].w=arr[i][j];
            }
        }
    }
    sort(nums+1,nums+tot+1,cmp);
    kruskalRebuild();
    dfs(cntu);
    for(int i=1;i<=n;i++){
        printf("%lld ",dp[cntu][i]);
    }
    return 0;
}