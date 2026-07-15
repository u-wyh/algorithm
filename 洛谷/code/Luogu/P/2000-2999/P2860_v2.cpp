// 这道题实际上是一个无向图缩点
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 1e4+5;

int n,m;
int col[MAXN];
int in[MAXN];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

bool vis[MAXM<<1];

int dfn[MAXN];
int low[MAXN];
int dfncnt,color;
int st[MAXN];
int top;

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    st[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        if(vis[i]){
            continue;
        }
        vis[i]=vis[((i-1)^1)+1]=true;
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        col[u]=++color;
        while(st[top]!=u){
            col[st[top--]]=color;
        }
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=nxt[j]){
            int v=to[j];
            if(col[v]!=col[i]){
                in[col[v]]++;
                in[col[i]]++;
            }
        }
    }
    int cnt1=0;
    for(int i=1;i<=color;i++){
        if(in[i]==2){
            cnt1++;
        }
    }
    cout<<(cnt1+1)/2<<endl;
    return 0;
}