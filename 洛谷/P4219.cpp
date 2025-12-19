#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = 3e6+5;

int n,q;
map<pair<int,int>,int>mp;
char op[MAXN];
int x[MAXN],y[MAXN];

int fa[MAXN];
int sz[MAXN];
int st[MAXN][2];
int top;

int head[MAXN<<2];
int nxt[MAXT];
int tox[MAXT];
int toy[MAXT];
int cnt=1;

long long ans[MAXN];

inline void addedge(int u,int x,int y){
    nxt[cnt]=head[u];
    tox[cnt]=x;
    toy[cnt]=y;
    head[u]=cnt++;
}

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void add(int jobl, int jobr, int jobx, int joby, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addedge(i, jobx, joby);
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobx, joby, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobx, joby, mid + 1, r, i << 1 | 1);
        }
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=q;i++){
        int v=mp[{x[i],y[i]}];
        if(v){
            if(op[v]=='Q'){
                v++;
            }
            add(v,i-1,x[i],y[i],1,q,1);
        }
        mp[{x[i],y[i]}]=i;
    }
    for(int i=1;i<=q;i++){
        int v=mp[{x[i],y[i]}];
        if(i==v){
            if(op[i]=='Q'){
                v++;
            }
            if(v<=q)
                add(v,q,x[i],y[i],1,q,1);
        }
    }
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(sz[fx]<sz[fy]){
        swap(fx,fy);
    }
    fa[fy]=fx;
    sz[fx]+=sz[fy];
    st[++top][0]=fx;
    st[top][1]=fy;
}

void undo(){
    int fx=st[top][0];
    int fy=st[top--][1];
    fa[fy]=fy;
    sz[fx]-=sz[fy];
}

void dfs(int l, int r, int i) {
    int unioncnt=0;
    for(int ei=head[i];ei;ei=nxt[ei]){
        un(tox[ei],toy[ei]);
        unioncnt++;
    }
    if(l==r){
        if(op[l]=='Q'){
            ans[l]=1ll*sz[find(x[l])]*sz[find(y[l])];
        }
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1);
        dfs(mid+1,r,i<<1|1);
    }
    while(unioncnt--){
        undo();
    }
}

int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=q;i++){
        scanf(" %c %d %d",&op[i],&x[i],&y[i]);
        // cout<<op[i]<<' '<<x[i]<<' '<<y[i]<<endl;
        if(x[i]>y[i]){
            swap(x[i],y[i]);
        }
    }
    prepare();
    dfs(1,q,1);
    for(int i=1;i<=q;i++){
        if(op[i]=='Q'){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}