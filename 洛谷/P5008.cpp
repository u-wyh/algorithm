#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+10;
const int MAXM = 2e6+10;

int n,m,k;
int val[MAXN];
int in[MAXN];
bool self[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
bool instack[MAXN];
int top;
int col[MAXN];
int minn[MAXN];
bool used[MAXN];
bool circle[MAXN];
int sz[MAXN];
int color;

int candidate[MAXN];
int len;

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

void tarjan(int u){
    low[u]=dfn[u]=++dfncnt;
    instack[u]=true;
    st[++top]=u;
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
    if(dfn[u]==low[u]){
        col[u]=++color;
        sz[color]++;
        instack[u]=false;
        minn[color]=val[u];
        while(st[top]!=u){
            int v=st[top];
            instack[v]=false;
            col[v]=color;
            minn[color]=min(minn[color],val[v]);
            sz[color]++;
            top--;
        }
        top--;
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        if(u==v){
            self[u]=true;
        }
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        int c=col[i];
        if(minn[c]==val[i]&&!used[c]){
            used[c]=true;
        }
        else{
            candidate[++len]=val[i];
        }

        if(self[i]){
            circle[c]=true;
        }
    }

    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(col[u]!=col[v]){
                in[col[v]]++;
            }
        }
    }

    for(int i=1;i<=color;i++){
        if(in[i]!=0){
            candidate[++len]=minn[i];
        }
        else if(circle[i]){
            candidate[++len]=minn[i];
        }
    }

    sort(candidate+1,candidate+len+1,cmp);
    // for(int i=1;i<=len;i++){
    //     cout<<candidate[i]<<' ';
    // }
    // cout<<endl;
    int res=0;
    for(int i=1;i<=min(k,len);i++){
        // cout<<candidate[i]<<' ';
        res+=candidate[i];
    }
    // cout<<endl;
    cout<<res<<endl;
    return 0;
}