#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MOD = 1e9+7;

vector<int>col[MAXN];
int n,m;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt;
int dp[MAXN][MAXN];

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
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

int dfs(int u,int f,int c){
    if(dp[u][c]!=0){
        return dp[u][c];
    }
    long long ans=1;
    bool flag=1;
    for(int ei=head[u];ei>0;ei=Next[ei]){
        int v=to[ei];
        if(v!=f){
            flag=0;
            for(int i=0;i<col[v].size();i++){
                int w=col[v][i];
                if(w!=c){
                    ans*=dfs(v,u,w);
                    ans%=MOD;
                }
            }
        }
    }
//    if(flag){
//        ans=0;
//    }
    dp[u][c]=(int)ans;
    return (int)ans;
}

int main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;i++){
        int k;
        k=read();
        for(int j=1;j<=k;j++){
            int c;
            cin>>c;
            col[i].push_back(c);
        }
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    long long ans=0;
    for(int i=0;i<col[1].size();i++){
        ans+=dfs(1,0,col[1][i]);
        ans%=MOD;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<dp[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
