// https://www.luogu.com.cn/problem/P3914
// 题意：给出一棵 N 个节点的树和 M 种颜色（编号 1..M），
// 每个节点 i 有一个允许使用的颜色列表（含 k_i 种颜色）。
// 求相邻节点颜色不同的合法染色方案总数，对 10^9 + 7 取模。
// 数据范围：1 <= N <= 5000，1 <= M <= 5000。
// 算法标签：树形动态规划、记忆化搜索
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
