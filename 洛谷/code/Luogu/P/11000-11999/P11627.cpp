#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n;
int res=0;

int root;
int sz[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int id[MAXN<<1];
int cnt=1;

int sum[MAXN<<2];
int tim[MAXN<<2];
int ans[MAXN<<2];

struct node{
    int sz,id;
};
// vector<node>vec[MAXN];
vector<node>vec;
// node nums[MAXN];
int dep[MAXN];
int weight[MAXN];
// int minnode[MAXN];
int edgeid[MAXN];
int now;

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

inline void addedge(int u,int v,int i){
    nxt[cnt]=head[u];
    to[cnt]=v;
    id[cnt]=i;
    head[u]=cnt++;
}

void up(int x){
    // sum[x]=(sum[x<<1]+sum[x<<1|1])%MOD;
    sum[x]=sum[x<<1]+sum[x<<1|1];
    tim[x]=tim[x<<1]+tim[x<<1|1];
    // ans[x]=(ans[x<<1]+ans[x<<1|1]+tim[x<<1]*sum[x<<1|1])%MOD;
    ans[x]=ans[x<<1]+ans[x<<1|1]+tim[x<<1]*sum[x<<1|1];
}

void add(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tim[i]+=jobv;
        sum[i]+=jobv*l;
        // sum[i]%=MOD;
        if (jobv == 1) {
            ans[i] += tim[i] * pos;
        } else {
            ans[i] -= (tim[i] + 1) * pos;
        }
        // ans[i]%=MOD;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            add(pos,jobv,l,mid,i<<1);
        }
        else{
            add(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void dfs1(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
    if(u!=1){
        add(sz[u],1,1,n,1);
    }
}

void dfs2(int u,int fa){
    int pre=0;
    if(fa!=0){
        pre=sz[u];
        add(sz[u],-1,1,n,1);
        add(n-sz[u],1,1,n,1);
        sz[fa]=n-sz[u];
        sz[u]=n;
        // res=max(res,ans[1]);
        if(res<ans[1]){
            res=ans[1];
            root=u;
        }
        else if(res==ans[1]&&u<root){
            root=u;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs2(v,u);
        }
    }
    if(fa!=0){
        sz[u]=pre;
        sz[fa]=n;
        add(sz[u],1,1,n,1);
        add(n-sz[u],-1,1,n,1);
    }
}

// bool cmp(node a,node b){
//     if(sz[a.u]==sz[b.u]){
//         return minnode[a.u]<minnode[a.v];
//     }
//     return sz[a.u]>sz[b.u];
// }

bool cmp(node a,node b){
    if(a.sz!=b.sz){
        return a.sz>b.sz;
    }
    return a.id>b.id;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            // minnode[v]=id[i];
            edgeid[v]=id[i];
            dfs(v,u);
            // minnode[u]=min(minnode[u],minnode[v]);
            sz[u]+=sz[v];
            // vec[u].push_back({v,id[i]});
        }
    }
    if(u!=root){
        vec.push_back({sz[u],edgeid[u]});
    }
}

// void dfs(int u){
//     sort(vec[u].begin(),vec[u].end(),cmp);
//     for(int i=0;i<(int)vec[u].size();i++){
//         node tmp=vec[u][i];
//         weight[tmp.v]=now--;
//         dfs(tmp.u);
//     }
// }

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        // nums[i]={u,v};
        addedge(u,v,i);
        addedge(v,u,i);
    }
    dfs1(1,0);

    // for(int i=1;i<=n;i++){
    //     cout<<sz[i]<<' ';
    // }
    // cout<<endl;

    res=max(res,ans[1]);
    root=1;
    dfs2(1,0);

    res%=MOD;
    res=(2*n*res)%MOD;
    cout<<res<<endl;
    
    // for(int i=1;i<=n;i++){
    //     cout<<sz[i]<<' ';
    // }
    // cout<<endl;

    cout<<root<<endl;
    now=n-1;
    dfs(root,0);
    // dfs(root);
    sort(vec.begin(),vec.end(),cmp);
    for(int i=1;i<n;i++){
        weight[vec[i-1].id]=n-i;
    }
    for(int i=1;i<n;i++){
        cout<<weight[i]<<' ';
    }
    return 0;
}