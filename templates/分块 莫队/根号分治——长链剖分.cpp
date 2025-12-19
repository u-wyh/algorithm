// https://www.luogu.com.cn/problem/solution/P3591
// 这道题完全就是长链剖分和根号分治结合的模板
// 代码有很多细节 尤其是在处理他们的lca  以及最后一步的公共点
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXB = 305;
const int MAXH = 16;

int n,blen;
int val[MAXN];

int nums[MAXN];
int step[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int st[MAXN][MAXH];
int dep[MAXN];
int len[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int seg[MAXN];
int dfncnt;

int f[MAXN][MAXB];

int high[MAXN];
int up[MAXN];
int down[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void setup(int u, int i, int v) {
    up[dfn[u] + i] = v;
}

int getup(int u, int i) {
    return up[dfn[u] + i];
}

void setdown(int u, int i, int v) {
    down[dfn[u] + i] = v;
}

int getdown(int u, int i) {
    return down[dfn[u] + i];
}

void dfs1(int u,int fa){
    st[u][0]=fa;
    for(int p=1;p<MAXH;p++){
        st[u][p]=st[st[u][p-1]][p-1];
    }
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        if(son[u]==0||len[son[u]]<len[v]){
            son[u]=v;
        }
    }
    len[u]=len[son[u]]+1;
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==son[u]||v==st[u][0]){
            continue;
        }
        dfs2(v,v);
    }
}

inline int query(int x, int k) {
    if(dep[x]<=k){
        return 0;
    }
    if (k == 0) {
        return x;
    }
    if (k == (1 << high[k])) {
        return st[x][high[k]];
    }
    x = st[x][high[k]];
    k -= (1 << high[k]);
    k -= dep[x] - dep[top[x]];
    x = top[x];
    return (k >= 0) ? getup(x, k) : getdown(x, -k);
}

void prepare(){
    blen=sqrt(n);
    dfs1(1,0);
    dfs2(1,1);
    high[0]=-1;
    for(int i=1;i<=n;i++){
        high[i]=high[i>>1]+1;
    }
    for(int u=1;u<=n;u++){
        if(top[u]==u){
            for(int i=0,a=u,b=u;i<len[u];i++,a=st[a][0],b=son[b]){
                setup(u,i,a);
                setdown(u,i,b);
            }
        }
    }
    for(int d=1;d<=blen;d++){
        for(int i=1;i<=n;i++){
            int u=seg[i];
            f[u][d]=(d<dep[u]?f[query(u,d)][d]:0)+val[u];
        }
    }
}

inline int lca(int a,int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = MAXH - 1; i >= 0; i--) {
        if (dep[st[a][i]] >= dep[b]) {
            a = st[a][i];
        }
    }
    if (a == b) return a;
    for (int i = MAXH - 1; i >= 0; i--) {
        if (st[a][i] != st[b][i]) {
            a = st[a][i];
            b = st[b][i];
        }
    }
    return st[a][0];
}

int querysum(int x,int y,int d){
    int fa=lca(x,y);
    if(d<=blen){
        int ans=0;
        int d1=dep[x]-dep[fa];
        int d2=dep[y]-dep[fa];
        int xx=query(x,d1/d*d);
        int yy=query(y,d2/d*d);
        ans=f[x][d]-f[xx][d]+val[xx]+f[y][d]-f[yy][d]+val[yy];
        if(xx==yy){
            ans-=val[fa];
        }
        return ans;
    }
    else{
        int ans=0;
        if((dep[fa]-dep[x])%d==0){
            ans-=val[fa];
        }
        while(dep[x]>=dep[fa]){
            ans+=val[x];
            x=query(x,d);
        }
        while(dep[y]>=dep[fa]){
            ans+=val[y];
            y=query(y,d);
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    prepare();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<n;i++){
        step[i]=read();
    }
    for(int i=1;i<n;i++){
        cout<<querysum(nums[i],nums[i+1],step[i])<<endl;
    }
    return 0;
}