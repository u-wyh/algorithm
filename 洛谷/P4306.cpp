#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int MAXM = 4e6+5;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int val[MAXN];
int cost[MAXN];
vector<int>vec[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
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
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
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
        val[color]++;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            val[color]++;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

bool vis[MAXN];

void dfs(int u){
    vis[u]=true;
    cost[u]=val[u];
    for(int i=0;i<vec[u].size();i++){
        int v=vec[u][i];
        if(!vis[v])
            dfs(v);
        cost[u]+=val[v];
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            int u=c-'0';
            if(u){
                addedge(i,j);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(col[v]!=col[i]){
                vec[i].push_back(v);
            }
        }
    }
    for(int i=1;i<=color;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    for(int i=1;i<=color;i++){
        cout<<i<<": "<<val[i]<<' '<<cost[i]<<endl;
    }
    int ans=0;
    for(int i=1;i<=color;i++){
        ans+=val[i]*cost[i];
    }
    cout<<ans<<endl;
    return 0;
}
/*
4
0110
0010
0001
0000
准备一个记忆数组  看看可以到达那些强联通分量  然后加上val
*/
