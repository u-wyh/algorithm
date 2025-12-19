#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 3e6+5;
const int INF = 1e9;

int n,m;

int a[MAXN];
int b[MAXN];
int c[MAXN];

int a1[MAXN][10];
int b1[MAXN][10];

int head[MAXN<<2];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int ans[MAXN][MAXN];

int tmp[20][MAXN];
int dp[MAXN];

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

//jobl 到 jobr上的节点挂上jobv
void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

void update(int v){
    for(int i=1;i<=a1[v][0];i++){
        for(int j=1000;j>=a1[v][i];j--){
            if(dp[j-a1[v][i]]>=0){
                dp[j]=max(dp[j],dp[j-a1[v][i]]+b1[v][i]);
            }
        }
    }
}

void dfs(int l,int r,int i,int dep){
    for(int i=0;i<=1000;i++){
        tmp[dep][i]=dp[i];
    }
    for(int ei=head[i];ei;ei=nxt[ei]){
        int v=to[ei];
        update(v);
    }
    if(l==r){
        for(int i=1;i<=1000;i++){
            dp[i]=max(dp[i-1],dp[i]);
        }
        for(int i=0;i<=1000;i++){
            ans[l][i]=dp[i];
        }
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1,dep+1);
        dfs(mid+1,r,i<<1|1,dep+1);
    }
    for(int i=0;i<=1000;i++){
        dp[i]=tmp[dep][i];
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        for(int j=1;c[i]>=j;j<<=1){
            a1[i][0]++;
            a1[i][a1[i][0]]=a[i]*j;
            b1[i][a1[i][0]]=b[i]*j;
            c[i]-=j;
        }
        if(c[i]){
            a1[i][0]++;
            a1[i][a1[i][0]]=a[i]*c[i];
            b1[i][a1[i][0]]=b[i]*c[i];
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read(),b[i]=read(),c[i]=read();
        if(i!=1){
            add(1,i-1,i,1,n,1);
        }
        if(i!=n){
            add(i+1,n,i,1,n,1);
        }
    }
    for(int i=1;i<=1000;i++){
        dp[i]=-INF;
    }
    prepare();
    dfs(1,n,1,0);
    m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        u++;
        printf("%d\n",ans[u][v]);
    }
    return 0;
}