#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 505;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int n,m;
int in[MAXN];
int cost[MAXN];
int val[MAXN];
int dad[MAXN];
int dp[MAXN][MAXM];//表示以i为头的子树上  必须要选择这个点  花费不超过j的情况下 价值最大是多少

int v[MAXN],w[MAXN];
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;

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

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        v[color]+=val[x];
        w[color]+=cost[x];
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            v[color]+=val[st[top]];
            w[color]+=cost[st[top]];
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

void dfs(int u){
    for(int i=w[u];i<=m;i++){
        dp[u][i]=v[u];
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        dfs(v);
        for(int j=m-w[u];j>=0;j--){
            for(int k=0;k<=j;k++){
                dp[u][j+w[u]]=max(dp[u][j+w[u]],dp[v][k]+dp[u][j+w[u]-k]);
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        cost[i]=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        dad[i]=read();
        if(dad[i]){
            vec[dad[i]].push_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(col[dad[i]]!=col[i]){
            addedge(col[dad[i]],col[i]);
            in[col[i]]++;
        }
    }
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            addedge(0,i);
        }
    }
    dfs(0);
    cout<<dp[0][m]<<endl;
    return 0;
}
