#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 5e4+5;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

int cost[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int in[MAXN],out[MAXN];
int val[MAXN],minn[MAXN];
bool instack[MAXN];
int n,m,k;

vector<int>vec[MAXN];

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

bool vis[MAXN];

void dfs(int u){
    for(int i=0;i<vec[u].size();i++){
        int v=vec[u][i];
        if(vis[v]){
            minn[u]=min(minn[u],minn[v]);
        }
        else{
            dfs(v);
            minn[u]=min(minn[u],minn[v]);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        cost[i]=INT_MAX;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        cost[u]=v;
    }
    k=read();
    for(int i=1;i<=k;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(col[i]!=col[v]){
                in[col[v]]++;
                out[col[i]]++;
                vec[col[i]].push_back(col[v]);
            }
        }
    }
    for(int i=1;i<=color;i++){
        val[i]=INT_MAX;
        minn[i]=INT_MAX;
    }
    for(int i=1;i<=n;i++){
        val[col[i]]=min(val[col[i]],cost[i]);
        if(cost[i]==INT_MAX)
            minn[col[i]]=min(minn[col[i]],i);
    }
    int ans=0,flag=1;
    for(int i=1;i<=color;i++){
        if(in[i]==0&&val[i]==INT_MAX){
            flag=0;
        }
        else if(in[i]==0){
            ans+=val[i];
        }
    }
    if(flag){
        cout<<"YES"<<endl;
        cout<<ans<<endl;
    }
    else{
        cout<<"NO"<<endl;
        int ans=INT_MAX;
        for(int i=1;i<=color;i++){
            if(in[i]==0&&val[i]==INT_MAX){
                dfs(i);
                ans=min(ans,minn[i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
