#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 5e4+5;

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m;
int val[MAXN];
int cost[MAXN];
int sz[MAXN];

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=color;i++){
        cost[i]=INT_MAX;
    }
    for(int i=1;i<=n;i++){
        if(cost[col[i]]==val[i]){
            sz[col[i]]++;
        }
        else if(cost[col[i]]>val[i]){
            sz[col[i]]=1;
            cost[col[i]]=val[i];
        }
    }
    int ans=1,ans1=0;
    for(int i=1;i<=color;i++){
        //cout<<sz[i]<<' '<<cost[i]<<endl;
        ans*=sz[i];
        ans1+=cost[i];
    }
    cout<<ans1<<' '<<ans;
    return 0;
}
