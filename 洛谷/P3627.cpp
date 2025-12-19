#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 5e5+5;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

vector<int>vec[MAXN];
int cost[MAXN];
int val[MAXN];
bool ok[MAXN];
bool okay[MAXN];

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m,s,k;

bool vis[MAXN];

void dfs(int u){
    int most=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(vis[v]){
            if(okay[v]){
                most=max(most,val[v]);
                okay[u]=true;
            }
        }
        else{
            dfs(v);
            if(okay[v]){
                most=max(most,val[v]);
                okay[u]=true;
            }
        }
    }
    val[u]+=most;
    vis[u]=true;
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

inline void addedge(int u,int v){
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
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        cost[i]=read();
    }
    s=read(),k=read();
    for(int i=1;i<=k;i++){
        int u;
        u=read();
        ok[u]=true;
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    //cout<<999<<endl;
    for(int i=1;i<=n;i++){
        val[col[i]]+=cost[i];
        okay[col[i]]=ok[i]?1:okay[col[i]];
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<vec[i].size();j++){
            int v=vec[i][j];
            if(col[i]!=col[v]){
                addedge(col[i],col[v]);
            }
        }
    }
    dfs(col[s]);
    cout<<val[col[s]];
    return 0;
}
