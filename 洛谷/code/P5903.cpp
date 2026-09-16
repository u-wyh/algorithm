#include<bits/stdc++.h>
using namespace std;
#define ui unsigned int
const int MAXN = 5e5+5;
const int MAXH = 21;

int n,m,p;
ui s;
int root;

int dep[MAXN];
int st[MAXN][MAXH];
int high[MAXN];
int len[MAXN];
int son[MAXN];
int top[MAXN];
int dfncnt;
int dfn[MAXN];

int up[MAXN];
int dn[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

ui get(ui x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    s = x;
    return x;
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    len[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v,u);
        len[u]=max(len[u],len[v]+1);
        if(len[u]==len[v]+1){
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[u]){
            dfs2(v,v);
        }
    }
}

void setup(int u,int i,int v){
    up[dfn[u]+i]=v;
}

void setdn(int u,int i,int v){
    dn[dfn[u]+i]=v;
}

int getup(int u,int i){
    return up[dfn[u]+i];
}

int getdn(int u,int i){
    return dn[dfn[u]+i];
}

void prepare(){
    high[0]=-1;
    for(int i=1;i<=n;i++){
        high[i]=high[i>>1]+1;
    }
    p=high[n];

    dfs1(root,0);
    dfs2(root,root);

    for(int u=1;u<=n;u++){
        if(top[u]==u){
            for(int i=0,a=u,b=u;i<len[u];i++,a=st[a][0],b=son[b]){
                setup(u,i,a);
                setdn(u,i,b);
            }
        }
    }
}

int query(int x,int k){
    if(k==0){
        return x;
    }
    if(k==(1<<high[k])){
        return st[x][high[k]];
    }

    x=st[x][high[k]];
    k-=(1<<high[k]);

    k-=dep[x]-dep[top[x]];
    x=top[x];
    return k>=0?getup(x,k):getdn(x,-k);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>s;
    for(int i=1;i<=n;i++){
        int fa;
        cin>>fa;
        if(fa==0){
            root=i;
        }
        else{
            addedge(fa,i);
        }
    }

    prepare();
    long long ans=0;
    for(int i=1,x,k,lastans=0;i<=m;i++){
        x=(get(s)^lastans)%n+1;
        k=(get(s)^lastans)%dep[x];
        lastans=query(x,k);
        ans^=(long long )i*lastans;
    }
    cout<<ans<<endl;
    return 0;
}