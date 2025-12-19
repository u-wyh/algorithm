#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXM = 1e5+5;
const int MAXH = 20;

int n,q,m,p;
int val[MAXN];
int arr[MAXN];

struct node{
    int l,r,lca,id;
};
node nums[MAXM];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];
int seg[MAXN<<1];
int sta[MAXN];
int over[MAXN];
int st[MAXN][MAXH];
int cntd;

int blen;
int bi[MAXN<<1];

bool vis[MAXN];
int cnt[MAXN];
int kind;

int ans[MAXM];

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    seg[++cntd]=u;
    sta[u]=cntd;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
    seg[++cntd]=u;
    over[u]=cntd;
}

inline int lca(int a,int b){
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

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool cmp(node a,node b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    return a.r<b.r;
}

void prepare(){
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }
    blen=sqrt(cntd);
    for(int i=1;i<=cntd;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(nums+1,nums+q+1,cmp);
}

void invert(int node){
    int c=val[node];
    if(vis[node]){
        if(--cnt[c]==0){
            kind--;
        }
    }
    else{
        if(++cnt[c]==1){
            kind++;
        }
    }
    vis[node]=!vis[node];
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=q;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int fa=nums[i].lca;
        int jobi=nums[i].id;
        while(winl>jobl){
            invert(seg[--winl]);
        }
        while(winr<jobr){
            invert(seg[++winr]);
        }
        while(winl<jobl){
            invert(seg[winl++]);
        }
        while(winr>jobr){
            invert(seg[winr--]);
        }
        if(fa){
            invert(fa);
        }
        ans[jobi]=kind;
        if(fa){
            invert(fa);
        }
    }
}

int main()
{
    n=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=q;i++){
        int u,v,fa;
        u=read(),v=read();
        if(sta[u]>sta[v]){
            swap(u,v);
        }
        fa=lca(u,v);
        if(u==fa){
            nums[i]={sta[u],sta[v],0,i};
        }
        else{
            nums[i]={over[u],sta[v],fa,i};
        }
    }
    prepare();
    compute();
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}