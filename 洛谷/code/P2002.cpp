//P2863
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 5e5+5;

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m;
int in[MAXN],out[MAXN];
int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
struct node{
    int u,v;
}edge[MAXM];

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
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        while(st[top]!=x){
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
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        edge[i].u=u,edge[i].v=v;
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=m;i++){
        if(col[edge[i].u]!=col[edge[i].v]){
            in[col[edge[i].v]]++;
            out[col[edge[i].u]]++;
        }
    }
    int ans=0;
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}

