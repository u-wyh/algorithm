#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int n,root;
int son1,son2;
long long ans;

int sz[MAXN];
int maxx[MAXN];
bool in[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int tree1[MAXN];
int tree2[MAXN];

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

void init(){
    ans=0,son1=0,son2=0;
    cnt=1;
    for(int i=1;i<=n+1;i++){
        head[i]=0;
        tree1[i]=0;
        tree2[i]=0;
        maxx[i]=0;
    }
}

inline int lowbit(int x){
    return x&-x;
}

void add(int *tree,int x,int v){
    x++;
    while(x<=n+1){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int *tree,int x){
    x++;
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void dfs1(int u,int fa){
    sz[u]=1;
    maxx[u]=0;
    bool flag=true;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
            maxx[u]=max(maxx[u],sz[v]);
            if(sz[v]*2>n){
                flag=false;
            }
        }
    }

    if(2*(n-sz[u])>n){
        flag=false;
    }

    if(flag){
        root=u;
    }
}

void dfs2(int u,int fa){
    add(tree1,sz[fa],-1);
    add(tree1,n-sz[u],1);

    if(u!=root){
        ans-=u*query(tree1,n-2*sz[u]-1);
        ans+=u*query(tree1,n-2*maxx[u]);
        ans-=u*query(tree2,n-2*sz[u]-1);
        ans+=u*query(tree2,n-2*maxx[u]);

        if(in[fa]){
            in[u]=true;
        }

        ans+=root*(sz[u]<=n-2*sz[in[u]?son2:son1]);
    }

    add(tree2,sz[u],1);

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs2(v,u);
        }
    }

    add(tree1,sz[fa],1);
    add(tree1,n-sz[u],-1);

    if(u!=root){
        ans+=u*query(tree2,n-2*sz[u]-1);
        ans-=u*query(tree2,n-2*maxx[u]);
    }
}

signed main()
{
    int T=read();
    while(T--){
        n=read();
        init();
        for(int i=1;i<n;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            addedge(v,u);
        }
        // cout<<777<<endl;
        dfs1(1,0);
        // cout<<888<<endl;
        dfs1(root,0);
        // cout<<999<<endl;

        son1=son2=0;
        for(int i=head[root];i;i=nxt[i]){
            int v=to[i];
            if(sz[v]>sz[son1]){
                son2=son1;
                son1=v;
            }
            else if(sz[v]>sz[son2]){
                son2=v;
            }
        }
        for(int i=1;i<=n;i++){
            add(tree1,sz[i],1);
            in[i]=0;
        }
        in[son1]=true;
        dfs2(root,0);
        cout<<ans<<endl;
    }
    return 0;
}