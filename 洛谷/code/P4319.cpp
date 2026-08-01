#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXT = 4e6+5;
const int MAXD = 32767;

int n,m;

int ex[MAXN];
int ey[MAXN];
int ew[MAXN];
int cnte;

int head[MAXD<<2];
int nxt[MAXT];
int to[MAXT];
int cntg=1;

int mstsum=1;
int ans[MAXD];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
bool rev[MAXN];
int sta[MAXN];

int maxedge[MAXN];

int rollbackedge[MAXN<<1];
int rollbacktype[MAXN<<1];
int opsize;

void up(int x){
    maxedge[x]=x<=n?0:x-n;
    if(ew[maxedge[ls[x]]]>ew[maxedge[x]]){
        maxedge[x]=maxedge[ls[x]];
    }
    if(ew[maxedge[rs[x]]]>ew[maxedge[x]]){
        maxedge[x]=maxedge[rs[x]];
    }
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

void down(int x) {
    if (rev[x]) {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
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

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

void undo(){
    int e = rollbackedge[opsize];
    int t = rollbacktype[opsize--];
    if (t == 1) {
        cut(ex[e], n + e);
        cut(ey[e], n + e);
        mstsum -= ew[e];
    } else {
        link(ex[e], n + e);
        link(ey[e], n + e);
        mstsum += ew[e];
    }
}

void backup(int e,int op){
    rollbackedge[++opsize]=e;
    rollbacktype[opsize]=op;
}

void addedge(int e){
    int x=ex[e];
    int y=ey[e];
    makeroot(x);
    if(findroot(y)!=x){
        link(x,n+e);
        link(y,n+e);
        backup(e,1);
        mstsum+=ew[e];
    }
    else{
        split(x,y);
        int pre=maxedge[y];
        if(ew[pre]>ew[e]){
            cut(ex[pre],n+pre);
            cut(ey[pre],pre+n);
            backup(pre,2);
            mstsum-=ew[pre];

            link(x,n+e);
            link(y,n+e);
            backup(e,1);
            mstsum+=ew[e];
        }
    }
}

void dfs(int l,int r,int i){
    int tmp=opsize;
    for(int e=head[i];e;e=nxt[e]){
        int v=to[e];
        addedge(v);
    }

    if(l==r){
        ans[l]=mstsum;
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1);
        dfs(mid+1,r,i<<1|1);
    }
    while(opsize>tmp){
        undo();
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    int day=MAXD-1;
    for(int i=1;i<n;i++){
        cin>>ex[++cnte];
        cin>>ey[cnte];
        cin>>ew[cnte];
        add(1,day,cnte,1,day,1);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>ex[++cnte];
        cin>>ey[cnte];
        cin>>ew[cnte];
        cin>>l>>r;
        add(l,r,cnte,1,day,1);
    }
    dfs(1,day,1);
    for(int i=1;i<=day;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}