#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 5e5+5;
const int MAXB = 300;
const int MAXH = 20;

int n,m,q;
int blen;
struct node{
    int u,v,w;
};
node nums[MAXM];

int cntu;
int fa[MAXN<<1];
int key[MAXN<<1];

int head[MAXN<<1];
int to[MAXN<<1];
int nxt[MAXN<<1];
int cnt=1;

int dep[MAXN<<1];
int st[MAXN<<1][MAXH];

int dfn[MAXN];
int seg[MAXN];
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

bool cmp(node a,node b){
    return a.w<b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void kruskalrebuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    sort(nums+1,nums+m+1,cmp);
    cntu=n;
    for(int i=1;i<=m;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            ++cntu;
            fa[fx]=fa[fy]=cntu;
            fa[cntu]=cntu;
            key[cntu]=nums[i].w;
            addedge(cntu,fx);
            addedge(cntu,fy);
        }
    }
}

void dfs(int u,int fa){
    if(u<=n){
        dfn[u]=++dfncnt;
        seg[dfncnt]=u;
    }
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

inline int lca(int x,int b){
    if(dep[x]<dep[b]) swap(x,b);
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[x][i]]>=dep[b]) x=st[x][i];
    }
    if(x==b) return x;
    for(int i=MAXH-1;i>=0;i--){
        if(st[x][i]!=st[b][i]){
            x=st[x][i];
            b=st[b][i];
        }
    }
    return st[x][0];
}

struct segment{
    int d;
    int cnt=0;
    int nums[MAXN];
    int rk[MAXN];
    int minn[MAXN<<2];
    int maxx[MAXN<<2];

    void prepare(){
        for(int i=1;i<=d;i++){
            for(int j=i;j<=n;j+=d){
                nums[++cnt]=j;
                rk[j]=cnt;
            }
        }
        // cout<<d<<":  ";
        // for(int i=1;i<=n;i++){
        //     cout<<nums[i]<<' ';
        // }
        // cout<<endl;
    }

    void up(int i){
        minn[i]=min(minn[i<<1],minn[i<<1|1]);
        maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
    }

    void build(int l,int r,int i){
        if(l==r){
            minn[i]=dfn[nums[l]];
            maxx[i]=dfn[nums[l]];
        }
        else{
            int mid=(l+r)>>1;
            build(l,mid,i<<1);
            build(mid+1,r,i<<1|1);
            up(i);
        }
    }

    pair<int,int>query(int jobl,int jobr,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            return {minn[i],maxx[i]};
        }
        else{
            int mid=(l+r)>>1;
            pair<int,int>ans={INT_MAX,INT_MIN};
            if(jobl<=mid){
                pair<int,int>tmp=query(jobl,jobr,l,mid,i<<1);
                ans={min(ans.first,tmp.first),max(ans.second,tmp.second)};
            }
            if(jobr>mid){
                pair<int,int>tmp=query(jobl,jobr,mid+1,r,i<<1|1);
                ans={min(ans.first,tmp.first),max(ans.second,tmp.second)};
            }
            return ans;
        }
    }
}root[121];

void prepare(){
    blen=min(120,(int)sqrt(n));
    for(int i=1;i<=blen;i++){
        root[i].d=i;
        root[i].prepare();
        root[i].build(1,n,1);
    }
}

void query(int l,int r,int k,int c){
    int st = (l <= c) ? c : c + k * ((l - c + k - 1) / k);
    int en = c + k * ((r - c) / k);
    // cout<<st<<' '<<en<<endl;
    if(k>blen){
        int low=INT_MAX,high=INT_MIN;
        for(int i=st;i<=en;i+=k){
            low=min(low,dfn[i]);
            high=max(high,dfn[i]);
        }
        low=seg[low];
        high=seg[high];
        cout<<key[lca(low,high)]<<endl;
    }
    else{
        st=root[k].rk[st];
        en=root[k].rk[en];
        pair<int,int>tmp=root[k].query(st,en,1,n,1);
        tmp.first=seg[tmp.first];
        tmp.second=seg[tmp.second];
        cout<<key[lca(tmp.first,tmp.second)]<<endl;
    }
}

int main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    kruskalrebuild();
    dfs(cntu,0);
    prepare();
    while(q--){
        int l,r,k,c;
        l=read(),r=read(),k=read(),c=read();
        query(l,r,k,c);
    }
    return 0;
}