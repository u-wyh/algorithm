#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 5e5+5;

int n,a,b;
int ans=INT_MAX;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

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

bool check(int u){
    if(dfn[u]<=dfn[a]&&dfn[u]>dfn[b]){
        return true;
    }
    if(dfn[u]>dfn[a]&&dfn[u]<=dfn[b]){
        return true;
    }
    return false;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]&&u!=a&&u!=b&&check(v)){
                ans=min(ans,u);
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    n=read();
    int u,v;
    u=read(),v=read();
    while(u+v!=0){
        addedge(u,v);
        addedge(v,u);
        u=read(),v=read();
    }
    a=read(),b=read();
    tarjan(1,0);
    if(ans==INT_MAX){
        cout<<"No solution"<<endl;
        return 0;
    }
    cout<<ans<<endl;
    return 0;
}