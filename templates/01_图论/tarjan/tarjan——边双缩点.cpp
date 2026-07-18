// https://www.luogu.com.cn/problem/P10953
//这道题是通过边双缩点  然后求lca
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int LIMIT = 20;

int n,m,qu,p;
int col[MAXN];
int color;
queue<int>q;

//原图上的边
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
bool vis[MAXM<<1];
bool bridge[MAXM<<1];
int cnt=1;

//边双缩点后的边
int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];
int cnt1=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int dep[MAXN];
int st[MAXN][LIMIT];

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

//找出所有的桥  准备缩点
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        if(vis[i]){
            continue;
        }
        vis[i]=vis[((i-1)^1)+1]=true;
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                bridge[i]=bridge[((i-1)^1)+1]=true;
            }
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
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
    tarjan(1);

    //缩点
    for(int i=1;i<=n;i++){
        if(!col[i]){
            color++;
            col[i]=color;
            q.push(i);
            while(!q.empty()){
                int u=q.front();
                q.pop();
                for(int j=head[u];j;j=nxt[j]){
                    int v=to[j];
                    if(col[v]||bridge[j]){
                        continue;
                    }
                    col[v]=color;
                    q.push(v);
                }
            }
        }
    }

    p=log2(color)+1;

    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=nxt[j]){
            int v=to[j];
            if(col[v]!=col[i]){
                if(col[v]<col[i]){
                    Addedge(col[v],col[i]);
                    Addedge(col[i],col[v]);
                }
            }
        }
    }

    dfs(1,0);

    qu=read();
    while(qu--){
        int a,b;
        a=read(),b=read();
        a=col[a],b=col[b];
        int ablca=lca(a,b);
        printf("%d\n",(dep[a]+dep[b]-2*dep[ablca]));
    }
    return 0;
}