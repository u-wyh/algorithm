#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;

struct Edge
{
    int to,nxt;
}e[10010];
int head[5010],cnt;

int num[5010];

void addedge(int u,int v,int val=0)
{
    e[++cnt]=(Edge){v,head[u]};
    head[u]=cnt;
}

int dp[5010][5010];
int tot[5010];
int n,m;

void dfs(int now,int fa)
{
    for(int i=head[now];i;i=e[i].nxt)
    {
        int vs=e[i].to;
        if(vs!=fa)
        {
            dfs(vs,now);
            for(int j=1;j<=m;j++)
            {
                dp[now][j]=((long long)dp[now][j]*(tot[vs]-dp[vs][j]+mod)%mod)%mod;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        tot[now]+=dp[now][i];
        tot[now]%=mod;
    }
}



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>num[i];
        for(int j=1;j<=num[i];j++)
        {
            int col;
            cin>>col;
            dp[i][col]=1;
        }
    }
    for(int j=1;j<n;j++)
    {
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    cout<<tot[1]<<endl;
}
/*
5
5
1 3
3 1 2 4
4 1 2 3 4
2 4 5
3 3 4 5
5 4 2 1 3 4 1 3
*/
