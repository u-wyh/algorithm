#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m,mod;

int in[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int head1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
int top;
bool instack[MAXN];
int color;
int col[MAXN];
int sz[MAXN];

map<pair<int,int>,bool>mp;

queue<int>q;
int dp[MAXN];
int cont[MAXN];

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

void tarjan(int u){
    low[u]=dfn[u]=++dfncnt;
    st[++top]=u;
    instack[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        } 
    }
    if(low[u]==dfn[u]){
        col[u]=++color;
        sz[color]++;
        instack[u]=false;
        while(st[top]!=u){
            instack[st[top]]=false;
            sz[color]++;
            col[st[top--]]=color;
        }
        top--;
    }
}

int main()
{
    n=read(),m=read(),mod=read();
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
                mp[{col[u],col[v]}]=true;
                Addedge(col[u],col[v]);
                in[col[v]]++;
            }
        }
    }
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            q.push(i);
            dp[i]=sz[i];
            cont[i]=1;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            in[v]--;
            if(dp[v]<dp[u]){
                dp[v]=dp[u];
                cont[v]=cont[u];
            }
            else if(dp[v]==dp[u]){
                cont[v]+=cont[u];
                cont[v]%=mod;
            }
            if(in[v]==0){
                q.push(v);
                dp[v]+=sz[v];
            }
        }
    }

    int maxans=0,maxcnt=0;
    for(int i=1;i<=color;i++){
        if(dp[i]>maxans){
            maxans=dp[i];
            maxcnt=cont[i];
        }
        else if(dp[i]==maxans){
            maxcnt+=cont[i];
            maxcnt%=mod;
        }
    }

    cout<<maxans<<endl<<maxcnt<<endl;

    return 0;
}