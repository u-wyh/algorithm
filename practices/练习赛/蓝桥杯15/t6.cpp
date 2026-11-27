#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int LIMIT = 18;

int n,q,p;
int arr[MAXN];
int val[MAXN];
int vis[MAXN][21];
int deep[MAXN];
int st[MAXN][LIMIT];
int cnt[1<<20];

int tot=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];

void addedge(int u,int v){
    nxt[tot]=head[u];
    to[tot]=v;
    head[u]=tot++;
}

void dfs(int u,int f){
    deep[u]=deep[f]+1;
    st[u][0]=f;
    for(int i=0;i<=19;i++){
        vis[u][i]=vis[f][i];
    }
    val[u]=val[f];
    val[u]|=(1<<arr[u]);
    vis[u][arr[u]]=u;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f)
            dfs(v,u);
    }
}

int lca(int a,int b){
    if(deep[a]<deep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(deep[st[a][i]]>=deep[b]){
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

int compute(int u,int v){
    int ans=val[v]^val[u];
    int tmp=val[u]&val[v];
    for(int i=0;i<=19;i++){
        if(tmp&(1<<i)){
            if(vis[u][i]!=vis[v][i]){
                ans+=(1<<i);
            }
        }
    }
    return ans;
}

int main()
{
    cnt[0]=0;
    for(int i=1;i<(1<<20);i++){
        cnt[i]=cnt[i-(i&-i)]+1;
        // cout<<i<<' '<<cnt[i]<<endl;
    }
    scanf("%d %d",&n,&q);
    p=log2(n);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i]--;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        int lcafa=st[lca(u,v)][0];
        cout<<cnt[compute(u,lcafa)|compute(v,lcafa)]<<endl;
    }
    return 0;
}