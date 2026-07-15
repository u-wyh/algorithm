#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int fa[MAXN];
int son[MAXN];
int len[MAXN];

int dfncnt;
int fid[MAXN];
int gid[MAXN];
long long f[MAXN];
long long g[MAXN<<1];

long long ans;

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

void setf(int u,int i,long long v){
    f[fid[u]+i]=v;
}

long long getf(int u,int i){
    return f[fid[u]+i];
}

void setg(int u,int i,long long v){
    g[gid[u]+i]=v;
}

long long getg(int u,int i){
    return g[gid[u]+i];
}

void dfs1(int u,int f){
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            if(son[u]==0||len[v]>len[son[u]]){
                son[u]=v;
            }
        }
    }
    len[u]=len[son[u]]+1;
}

void dfs2(int u,int top){
    fid[u]=++dfncnt;
    if(son[u]==0){
        gid[u]=2*fid[top];
        return ;
    }
    dfs2(son[u],top);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
    gid[u]=gid[son[u]]+1;
}

void dfs3(int u){
    setf(u,0,1);
    if(son[u]==0){
        return ;
    }
    dfs3(son[u]);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs3(v);
        }
    }
    for(int ei=head[u];ei;ei=nxt[ei]){
        int v=to[ei];
        if(v!=son[u]&&v!=fa[u]){
            for(int i=0;i<=len[v];i++){
                if(i<len[u]&&i-1>=0){
                    ans+=getg(u,i)*getf(v,i-1);
                }
                if(i+1<len[v]&&i>0){
                    ans+=getg(v,i+1)*getf(u,i);
                }
            }
            for(int i=0;i<=len[v];i++){
                if(i+1<len[v]){
                    setg(u,i,getg(u,i)+getg(v,i+1));
                }
                if(i-1>=0){
                    setg(u,i,getg(u,i)+getf(u,i)*getf(v,i-1));
                }
            }
            for(int i=0;i<=len[v];i++){
                if(i-1>=0){
                    setf(u,i,getf(u,i)+getf(v,i-1));
                }
            }
        }
    }
    ans+=getg(u,0);
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    dfs3(1);
    cout<<ans<<endl;
    return 0;
}