// https://www.luogu.com.cn/problem/P6805
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,q,root;
long long allodd;

int x[MAXN];
int y[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int eid[MAXM];
int cntg=1;
int deg[MAXN];

int father[MAXN];
int peid[MAXN];
int childcnt[MAXN];
int leafsum[MAXN];

int arr[MAXN];

int fa[MAXM];
int ls[MAXM];
int rs[MAXM];
bool rev[MAXM];
bool tag[MAXM];
int sta[MAXM];

bool isedge[MAXM];
int val[MAXM];
int edgecnt[MAXM];
int odd[MAXM];

inline void addedge(int u,int v,int id){
    nxt[cntg]=head[u];
    to[cntg]=v;
    eid[cntg]=id;
    head[u]=cntg++;
    deg[v]++;
}

void up(int x){
    edgecnt[x]=edgecnt[ls[x]]+edgecnt[rs[x]]+isedge[x];
    odd[x]=odd[ls[x]]+odd[rs[x]]+val[x];
}

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void reverse(int x) {
    if (x != 0) {
        swap(ls[x], rs[x]);
        rev[x] = !rev[x];
    }
}

void change(int x){
    if(x){
        odd[x]=edgecnt[x]-odd[x];
        if(isedge[x]){
            val[x]^=1;
        }
        tag[x]^=1;
    }
}

void down(int x) {
    if (rev[x]) {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
    }
    if(tag[x]){
        change(ls[x]);
        change(rs[x]);
        tag[x]=0;
    }
}

void rotate(int x) {
    int f = fa[x], g = fa[f];
    if (lr(x) == 0) {
        ls[f] = rs[x];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    } else {
        rs[f] = ls[x];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            ls[g] = x;
        } else {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
    up(f);
    up(x);
}

void splay(int x){
    int siz = 0;
    sta[++siz] = x;
    for (int y = x; !isroot(y); y = fa[y]) {
        sta[++siz] = fa[y];
    }
    while (siz != 0) {
        down(sta[siz--]);
    }
    while (!isroot(x)) {
        int f = fa[x];
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

void access(int x){
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        splay(x);
        rs[x] = y;
        up(x);
    }
}

void makeroot(int x){
    access(x);
    splay(x);
    reverse(x);
}

int findroot(int x){
    access(x);
    splay(x);
    down(x);
    while (ls[x] != 0) {
        x = ls[x];
        down(x);
    }
    splay(x);
    return x;
}

void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}

void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x){
        fa[x]=y;
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&fa[y]==x&&ls[y]==0&&rs[x]==y){
        fa[y]=rs[x]=0;
        up(x);
    }
}

void dfs(int u,int f){
    father[u]=f;
    childcnt[u]=0;
    leafsum[u]=(deg[u]==1);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        peid[v]=eid[i];
        dfs(v,u);
        childcnt[u]++;
        leafsum[u]+=leafsum[v];
    }
}

void prepare(){
    root=1;
    while(deg[root]==1){
        root++;
    }
    dfs(root,0);

    for(int u=1;u<=n;u++){
        if(u==root){
            continue;
        }
        int e=peid[u];
        int x=n+e;
        isedge[x]=true;
        val[x]=leafsum[u]&1;
        edgecnt[x]=1;
        odd[x]=val[x];
        allodd+=val[x];
    }
    for(int i=1;i<n;i++){
        int e=n+i;
        link(x[i],e);
        link(y[i],e);
    }
}

void changepath(int x){
    split(root,x);
    int old=odd[x];
    int cnt=edgecnt[x];
    allodd+=cnt-2*old;
    change(x);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<n;i++){
        cin>>x[i]>>y[i];
        addedge(x[i],y[i],i);
        addedge(y[i],x[i],i);
    }

    prepare();

    int baseleaves=leafsum[root];
    for(int i=1;i<=q;i++){
        int d;
        cin>>d;
        int leaves=baseleaves;
        for(int i=1;i<=d;i++){
            int x;
            cin>>x;
            arr[i]=x;

            if(childcnt[x]>0){
                changepath(x);
                leaves++;
            }
            childcnt[x]++;
        }
        if(leaves&1){
            cout<<-1<<endl;
        }
        else{
            long long ans=2ll*(n-1)-allodd+d;
            cout<<ans<<endl;
        }

        for(int i=d;i>=1;i--){
            int x=arr[i];
            childcnt[x]--;
            if(childcnt[x]>0){
                changepath(x);
            }
        }
    }
    return 0;
}