#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 20;

int n,m,q,p;
int v[MAXN];
int w[MAXN];
int c[MAXN];

struct QUERY{
    int l,r,t,lca,id;
};
struct UPDATE{
    int pos,val;
};
QUERY query[MAXN];
UPDATE update[MAXN];
int cntu,cntq;

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
long long happy;
long long ans[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

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

bool cmp(QUERY &a,QUERY &b){
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if (bi[a.r] != bi[b.r]) {
        return bi[a.r] < bi[b.r];
    }
    return a.t < b.t;
}

void prepare(){
    blen=max(1,(int)pow(cntd,2.0/3));
    for(int i=1;i<=cntd;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(query+1,query+cntq+1,cmp);
}

// 窗口不管是加入还是删除node
// 只要遇到node就翻转信息即可
void invert(int node) {
    int candy = c[node];
    if (vis[node]) {
        happy -= 1LL * v[candy] * w[cnt[candy]--];
    } else {
        happy += 1LL * v[candy] * w[++cnt[candy]];
    }
    vis[node] = !vis[node];
}

// 上节课带修莫队的重要过程
// tim为生效或者撤销的修改时间点，公园更换糖果
void moveTime(int tim) {
    int pos = update[tim].pos;
    int oldVal = c[pos];
    int newVal = update[tim].val;
    if (vis[pos]) {
        // 如果当前公园生效中
        // 老糖果invert效果
        invert(pos);
        // 新老糖果换位
        c[pos] = newVal;
        update[tim].val = oldVal;
        // 新糖果invert效果
        invert(pos);
    } else {
        // 如果当前公园不在生效中
		// 新老糖果换位即可
        c[pos] = newVal;
        update[tim].val = oldVal;
    }
}

void compute(){
    int winl=1,winr=0,wint=0;
    for(int i=1;i<=cntq;i++){
        int jobl=query[i].l;
        int jobr=query[i].r;
        int jobt=query[i].t;
        int fa=query[i].lca;
        int jobi=query[i].id;
        while (winl > jobl) {
            invert(seg[--winl]);
        }
        while (winr < jobr) {
            invert(seg[++winr]);
        }
        while (winl < jobl) {
            invert(seg[winl++]);
        }
        while (winr > jobr) {
            invert(seg[winr--]);
        }
        while (wint < jobt) {
            moveTime(++wint);
        }
        while (wint > jobt) {
            moveTime(wint--);
        }
        if (fa > 0) {
            invert(fa);
        }
        ans[jobi] = happy;
        if (fa > 0) {
            invert(fa);
        }
    }
}

int main()
{
    n=read(),m=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<=m;i++){
        v[i]=read();
    }
    for(int i=1;i<=n;i++){
        w[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        c[i]=read();
    }
    dfs(1,0);
    for(int i=1;i<=q;i++){
        int op,x,y;
        op=read(),x=read(),y=read();
        if(op==0){
            cntu++;
            update[cntu]={x,y};
        }
        else{
            if(sta[x]>sta[y]){
                swap(x,y);
            }
            int fa=lca(x,y);
            if(x==fa){
                query[++cntq]={sta[x],sta[y],cntu,0,cntq};
            }
            else{
                query[++cntq]={over[x],sta[y],cntu,fa,cntq};
            }
        }
    }
    prepare();
    compute();
    for(int i=1;i<=cntq;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}