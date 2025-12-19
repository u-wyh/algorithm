#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 20;
const int INF = 1e9;

int n,q,p;
struct node{
    int x,y,v,c,s;
};
node nums[MAXN];

int qid[MAXN];
int x[MAXN];
int y[MAXN];
int fa[MAXN];
int limit[MAXN];
long long k[MAXN];

int lset[MAXN];
int rset[MAXN];
int ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

int dep[MAXN];
int st[MAXN][MAXH];
int dfn[MAXN];
int seg[MAXN];
int sz[MAXN];
int dfncnt;

int stmaxmin[MAXN][MAXH];
long long tree[MAXN<<2];

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    dfn[u]=++dfncnt;
    seg[dfncnt]=dfn[u];
    sz[u]=1;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            stmaxmin[v][0]=w;
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
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

bool cmp(node a,node b){
    return a.v<b.v;
}

int get(int x, int anc) {
    int res = INF;
    for (int i = p; i >= 0; i--) {
        if (dep[st[x][i]] >= dep[anc]) {
            res = min(res, stmaxmin[x][i]);
            x = st[x][i];
        }
    }
    return res;
}

void prepare(){
    dfs(1,0);
    for(int i=1;i<=p;i++){
        for(int j=1;j<=n;j++){
            stmaxmin[j][i]=min(stmaxmin[j][i-1],stmaxmin[st[j][i-1]][i-1]);
        }
    }
    for(int i=1;i<=q;i++){
        fa[i]=lca(x[i],y[i]);
        limit[i]=min(get(x[i], fa[i]), get(y[i], fa[i]));
    }
    for(int i=1;i<n;i++){
        if(dep[nums[i].x]<dep[nums[i].y]){
            swap(nums[i].x,nums[i].y);
        }
    }
    sort(nums+1,nums+n,cmp);
}

int find1(int val){
    int l=1,r=n-1,ans=n;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid].v>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find2(int val){
    int l=1,r=n-1,ans=n;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid].v>val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void lazy(int i,long long val){
    tree[i]+=val;
}

void down(int i){
    if(tree[i]){
        lazy(i<<1,tree[i]);
        lazy(i<<1|1,tree[i]);
        tree[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

long long query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);            
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

long long query(int x){
    return query(dfn[x],1,n,1);
}

void add(int x,int val){
    add(dfn[x],dfn[x]+sz[x]-1,val,1,n,1);
}

void compute(int ql,int qr,int vl,int vr){
    if(ql>qr){
        return ;
    }
    if(vl==vr){
        for(int i=ql;i<=qr;i++){
            ans[qid[i]]=vl;
        }
    }
    else{
        int mid=(vl+vr)>>1;
        int lt=find1(vl);
        int rt=find2(mid)-1;
        for(int i=lt;i<=rt;i++){
            add(nums[i].x,nums[i].c);
        }
        int lsz=0,rsz=0;
        for(int i=ql;i<=qr;i++){
            int id=qid[i];
            if(limit[id]<=mid){
                lset[++lsz]=id;
                continue;
            }
            long long need=query(x[id])+query(y[id])-2*query(fa[id]);
            if(need>k[id]){
                lset[++lsz]=id;
            }
            else{
                rset[++rsz]=id;
                k[id]-=need;
            }
        }
        for (int i = 1; i <= lsz; i++) {
            qid[ql + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsz; i++) {
            qid[ql + lsz + i - 1] = rset[i];
        }
        // 撤回数据状况
        for (int i = lt; i <= rt; i++) {
            add(nums[i].x,-nums[i].c);
        }
        // 左右两侧各自递归
        compute(ql, ql + lsz - 1, vl, mid);
        compute(ql + lsz, qr, mid+1, vr);
    }
}

int main()
{
    scanf("%d",&n);
    p=log2(n)+1;
    int maxx=0;
    for(int i=1;i<n;i++){
        scanf("%d %d %d %d %d",&nums[i].x,&nums[i].y,&nums[i].v,&nums[i].c,&nums[i].s);
        addedge(nums[i].x,nums[i].y,nums[i].s);
        addedge(nums[i].y,nums[i].x,nums[i].s);
        maxx=max(maxx,nums[i].s);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        qid[i]=i;
        scanf("%d %d %lld",&x[i],&y[i],&k[i]);
    }
    prepare();

    // for(int i=1;i<=n;i++){
    //     // cout<<i<<":  "<<sz[i]<<endl;
    //     cout<<i<<":  "<<nums[i].x<<' '<<nums[i].y<<endl;
    // }

    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<stmaxmin[i][0]<<endl;
    // }
    // cout<<endl;

    // for(int i=1;i<=q;i++){
    //     cout<<i<<":    "<<x[i]<<' '<<y[i]<<' '<<limit[i]<<' '<<fa[i]<<endl;
    // }
    // cout<<endl;
    // cout<<maxx<<endl;

    compute(1,q,1,maxx);
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
/*
6
1 2 5 7 10
1 3 4 8 9
3 4 7 1 15
3 5 6 3 11
3 6 5 6 8
3
2 4 15
6 4 5
3 5 10
*/