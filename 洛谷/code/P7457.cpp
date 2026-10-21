// https://www.luogu.com.cn/problem/P7457
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*40;

int n,q;

int fa[MAXN];
int sz[MAXN];
int rollback[MAXN][2];
int opsize;

int op[MAXN];
int x[MAXN];
int y[MAXN];
int w[MAXN];

int ans[MAXN];

map<pair<int,int>,int>edge;
int cnte;
int val[MAXN];
int st[MAXN];
int en[MAXN];
int bel[MAXN];

int head[MAXN<<2];
int nxt[MAXT];
int to[MAXT];
int cntg=1;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void add(int jobl,int jobr,int jobe,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobe);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobe,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobe,mid+1,r,i<<1|1);
        }
    }
}

void prepare(){
    for(int i=1;i<=q;i++){
        if(op[i]==0){
            edge[{x[i],y[i]}]=++cnte;
            val[cnte]=w[i];
            st[cnte]=i;
            bel[cnte]=i;
        }
        else if(op[i]==1){
            int e=edge[{x[i],y[i]}];
            edge[{x[i],y[i]}]=0;
            en[e]=i-1;
            add(st[e],en[e],bel[e],1,q,1);
        }
    }
    for(int i=1;i<=cnte;i++){
        if(en[i]==0){
            add(st[i],q,bel[i],1,q,1);
        }
    }
    for(int i=1;i<=q;i++){
        ans[i]=-1;
    }
}

int find(int x){
    return x==fa[x]?x:find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(sz[fx]>sz[fy]){
            swap(fx,fy);
        }
        fa[fx]=fy;
        sz[fy]+=sz[fx];

        ++opsize;
        rollback[opsize][0]=fx;
        rollback[opsize][1]=fy;
    }
}

void undo(){
    int x=rollback[opsize][0];
    int y=rollback[opsize][1];
    opsize--;

    fa[x]=x;
    sz[y]-=sz[x];
}

void dfs(int l,int r,int i,int limit){
    int cnt=0;
    for(int e=head[i];e;e=nxt[e]){
        int v=to[e];
        if(w[v]<=limit){
            int a=x[v];
            int b=y[v];
            if(find(a)!=find(b)){
                un(a,b);
                cnt++;
            }
        }
    }
    if(l==r){
        if(op[l]==2){
            if(ans[l]==-1 && find(x[l])==find(y[l])){
                ans[l]=limit;
            }
        }
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1,limit);
        dfs(mid+1,r,i<<1|1,limit);
    }
    while(cnt){
        cnt--;
        undo();
    }
}

void compute(){
    for(int limit=0;limit<10;limit++){
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
        }
        dfs(1,q,1,limit);
    }
}

int main()
{
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        cin>>op[i]>>x[i]>>y[i];
        x[i]++,y[i]++;
        if(x[i]>y[i]){
            swap(x[i],y[i]);
        }
        if(op[i]==0){
            cin>>w[i];
        }
    }

    prepare();

    compute();

    for(int i=1;i<=q;i++){
        if(op[i]==2){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}