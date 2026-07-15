#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int head1[MAXN];
int nxt1[MAXN];
int to1[MAXN];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
bool instack[MAXN];
int top;
int color;
int col[MAXN];
int sz[MAXN];
int in[MAXN];

map<pair<int,int>,bool>mp;

bool vis[MAXN];
queue<int>q;

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void Addedge(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt;
    instack[u] = true;
    st[++top] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        col[u]=++color;
        sz[color]++;
        instack[u]=false;
        while(st[top]!=u){
            int v=st[top];
            instack[v]=false;
            col[v]=color;
            sz[color]++;
            top--;
        }
        top--;
    }
}

int main()
{
    n=read(),m=read();
    if(n==1){
        cout<<"1.000000";
        return 0;
    }
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
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(col[u]!=col[v]&&!mp[{col[u],col[v]}]){
                Addedge(col[u],col[v]);
                in[col[v]]++;
                mp[{col[u],col[v]}]=true;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            ans++;
        }
    }
    for(int i=1;i<=color;i++){
        if(in[i]==0&&sz[i]==1){
            bool flag=true;
            for(int ei=head1[i];ei;ei=nxt1[ei]){
                int v=to1[ei];
                if(in[v]==1){
                    flag=false;
                    break;
                }
            }
            if(flag){
                ans--;
                break;
            }
        }
    }
    printf("%.6lf\n",1-1.0*ans/n);
    return 0;
}