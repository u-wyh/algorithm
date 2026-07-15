#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;

int cnt=1;
int head[MAXN];
int Next[MAXN];
int to[MAXN];

int n,m;
int f[MAXN][MAXN];
int sum[MAXN];

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
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    sum[u]=1;
    f[u][1]=0,f[u][0]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        dfs(v);
        sum[u]+=sum[v];
        for(int j=sum[u];j;j--){
            f[u][j]+=1;
            for(int k=0;k<=min(sum[v],j-1);k++){
                f[u][j]=min(f[u][j],f[u][j-k]+f[v][k]);
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=1e9;
        }
    }
    dfs(1);
    int ans=f[1][m];
    for(int i=2;i<=n;i++){
        ans=min(ans,f[i][m]+1);
    }
    cout<<ans<<endl;
    return 0;
}
