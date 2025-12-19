#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int LIMIT = 17;

int st[MAXN][LIMIT+1];
vector<int>path[MAXN];
int f[MAXN];
int deep[MAXN];
int n,m;
int cnt=0;
int id[MAXN];
int rk[MAXN];
int sz[MAXN];
int tree[MAXN<<2];
int change[MAXN<<2];
int len[MAXN<<2];

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

void dfs1(int u,int fa){
    deep[u]=deep[fa]+1;
    st[u][0]=fa;
    sz[u]=1;
    for(int i=1;i<=LIMIT;i++){
        if(st[u][i-1]){
            st[u][i]=st[st[u][i-1]][i-1];
        }
    }
    for(int i=0;i<path[u].size();i++){
        int v=path[u][i];
        f[u]=u;
        dfs1(v,u);
        sz[u]+=sz[v];
        f[u]=min(f[u],f[v]);
    }
}

bool cmp(int a,int b){
    return f[a]<f[b];
}

void dfs2(int u){
    //cout<<444<<endl;
    if(!path[u].empty()){
        sort(path[u].begin(),path[u].end(),cmp);
        for(int i=0;i<path[u].size();i++){
            int v=path[u][i];
            dfs2(v);
        }
    }
    id[u]=++cnt;
    rk[cnt]=u;
}

void downlazy(int i,int v){
    tree[i]=len[i]*v;
    change[i]=v;
}

void down(int i){
    if(change[i]!=-1){
        downlazy(i<<1,change[i]);
        downlazy(i<<1|1,change[i]);
        change[i]=-1;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    //cout<<666<<endl;
    if(jobl<=l&&r<=jobr){
        downlazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid)
            update(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid)
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl==jobr&&jobl==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=0;
        down(i);
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

void build(int l,int r,int i){
    len[i]=r-l+1;
    if(l==r){
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    change[i]=-1;
}

int query(int k,int l,int r,int i){
    //cout<<55<<endl;
    if(l==r){
        return l;
    }
    down(i);
    int lsize=len[i<<1]-tree[i<<1];
    int mid=(l+r)/2;
    if(lsize>=k){
        return query(k,l,mid,i<<1);
    }
    else{
        return query(k-lsize,mid+1,r,i<<1|1);
    }
}

int main()
{
    n=read(),m=read();
    int root=1;
    for(int i=1;i<=n;i++){
        int v=read();
        if(v==0){
            root=i;
        }
        path[v].push_back(i);
    }
    //cout<<' '<<root<<endl;
    dfs1(root,0);
    dfs2(root);
    build(1,n,1);
//    for(int i=1;i<=n;i++){
//        cout<<i<<": "<<id[i]<<endl;
//    }
    for(int i=1;i<=m;i++){
        int op,u;
        op=read(),u=read();
        if(op==1){
            if(u>len[1]-tree[1]){
                u=len[1]-tree[1];
            }
            int ans=query(u,1,n,1);
            cout<<rk[ans]<<endl;
            update(1,ans,1,1,n,1);
        }
        else{
            int ans=0;
            for(int i=LIMIT;i>=0;i--){
                if(query(id[st[u][i]],id[st[u][i]],1,n,1)){
                    ans=st[u][i];
                }
            }
            if(ans!=0){
                update(id[ans],id[ans],0,1,n,1);
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
