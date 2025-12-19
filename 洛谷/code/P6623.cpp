#include<bits/stdc++.h>
using namespace std;
const int MAXN = 525015;
const int MAXT = 21*MAXN;

int n;
int val[MAXN];
long long ans;

int root[MAXN];
int trie[MAXT][2];
int sz[MAXT];
int eorval[MAXT];
int cnt;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

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
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void update(int u){
    int l=trie[u][0];
    int r=trie[u][1];

    sz[u]=sz[l]+sz[r];

    eorval[u]=(eorval[l]^eorval[r])<<1;
    if(sz[r]&1){
        eorval[u]^=1;
    }
}

void addone(int u){
    if(u==0){
        return ;
    }
    swap(trie[u][0],trie[u][1]);
    addone(trie[u][0]);
    update(u);
}

int insert(int u,int bit,int x){
    if(u==0){
        u=++cnt;
    }

    if(bit>20){
        sz[u]++;
        return u;
    }

    int b=(x>>bit)&1;
    trie[u][b]=insert(trie[u][b],bit+1,x);

    update(u);

    return u;
}

int merge(int a,int b,int bit){
    if(a==0||b==0){
        return a+b;
    }
    if(bit>20){
        sz[a]+=sz[b];
        return a;
    }
    trie[a][0]=merge(trie[a][0],trie[b][0],bit+1);
    trie[a][1]=merge(trie[a][1],trie[b][1],bit+1);
    update(a);
    return a;
}

void dfs(int u){
    root[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        addone(root[v]);
        root[u]=merge(root[u],root[v],0);
    }
    root[u]=insert(root[u],0,val[u]);
    ans+=eorval[root[u]];
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int fa=read();
        addedge(fa,i);
    }
    dfs(1);
    cout<<ans<<endl;
    return 0;
}