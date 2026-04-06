#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXM = 1e5+5;
const int MAXH = 20;

int n,m,p;
int val[MAXN];
int len;
int sortv[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int cntd;
int sta[MAXN<<1];
int ove[MAXN<<1];
int seg[MAXN<<1];

int dep[MAXN];
int st[MAXN][MAXH];

struct node{
    int l,r,lca,id;
};
node nums[MAXM];
int ans[MAXM];

int blen;
int bi[MAXN<<1];

int kind;
int cnt[MAXN];
bool vis[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    sta[u]=++cntd;
    seg[cntd]=u;
    dep[u]=dep[fa]+1;

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
    ove[u]=++cntd;
    seg[cntd]=u;
}

int find(int val){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sortv[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=n;i++){
        sortv[i]=val[i];
    }
    sort(sortv+1,sortv+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sortv[i]!=sortv[i-1]){
            sortv[++len]=sortv[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    p=log2(n)+1;
    dfs(1,0);
    
    blen=sqrt(2*n);
    for(int i=1;i<=2*n;i++){
        bi[i]=(i-1)/blen+1;
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

bool cmp(node &a,node &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    if(bi[a.l]&1){
        return a.r<b.r;
    }
    else{
        return a.r>b.r;
    }
}

void add(int val){
    cnt[val]++;
    if(cnt[val]==1){
        kind++;
    }
}

void del(int val){
    cnt[val]--;
    if(cnt[val]==0){
        kind--;
    }
}

void change(int pos){
    vis[pos]^=1;
    if(vis[pos]){
        add(val[pos]);
    }
    else{
        del(val[pos]);
    }
}

void compute(){
    sort(nums+1,nums+m+1,cmp);
    int winl=1,winr=0;
    for(int i=1;i<=m;i++){
        int l=nums[i].l;
        int r=nums[i].r;
        int lca=nums[i].lca;
        int id=nums[i].id;

        while(winl>l){
            change(seg[--winl]);
        }
        while(winr<r){
            change(seg[++winr]);
        }
        while(winl<l){
            change(seg[winl++]);
        }
        while(winr>r){
            change(seg[winr--]);
        }
        if(lca){
            change(lca);
        }
        ans[id]=kind;
        if(lca){
            change(lca);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int fa=lca(u,v);
        if(sta[u]>sta[v]){
            swap(u,v);
        }
        if(fa==u){
            nums[i]={sta[u],sta[v],0,i};
        }
        else{
            nums[i]={ove[u],sta[v],fa,i};
        }
    }

    compute();

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}