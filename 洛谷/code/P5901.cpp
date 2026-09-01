#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;
const int MAXR = 25005;
const int MAXH = 205;
const int B = 1000;
const int INF = 1e9;

const int HSIZE = 1<<19;
const int HMASK = HSIZE-1;

int n,R,q;

int fa[MAXN];
int col[MAXN];

// 树的邻接表
int head[MAXN];
int nxt[MAXN];

// DFS序及子树右端点
int ord[MAXN];
int out[MAXN];
int tim;

// 每个地区在DFS序数组中的连续区间
int cnt[MAXR];
int st[MAXR];
int cur[MAXR];
int ptin[MAXN];
int pout[MAXN];

// 大地区编号
int hid[MAXR];
int hreg[MAXH];
int hcnt;

// f[x][r]：大地区x作为祖先，地区r作为后代
// g[x][r]：地区r作为祖先，大地区x作为后代
int f[MAXH][MAXR];
int g[MAXH][MAXR];

// 小地区询问记忆化哈希表
unsigned int hkey[HSIZE];
int hval[HSIZE];

inline int read(){
    int x=0;
    char ch=getchar();

    while(ch<'0'||ch>'9')
        ch=getchar();

    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }

    return x;
}

void dfs(int x){
    ord[++tim]=x;

    for(int y=head[x];y;y=nxt[y])
        dfs(y);

    out[x]=tim;
}

inline void addval(int &x,int y){
    long long v=(long long)x+y;
    x=v>=INF?INF:v;
}

void buildHeavy(int id){
    int c=hreg[id];

    // nxt[x]暂存x的严格祖先中属于地区c的数量
    nxt[1]=0;

    for(int x=1;x<=n;x++){
        if(x>1)
            nxt[x]=nxt[fa[x]]+(col[fa[x]]==c);

        addval(f[id][col[x]],nxt[x]);
    }

    // head[x]暂存x子树内属于地区c的节点数量
    for(int x=1;x<=n;x++)
        head[x]=(col[x]==c);

    for(int x=n;x>=2;x--)
        head[fa[x]]+=head[x];

    for(int x=1;x<=n;x++){
        int v=head[x]-(col[x]==c);
        addval(g[id][col[x]],v);
    }
}

long long calcMerge(int a,int b){
    int la=st[a];
    int ra=la+cnt[a];
    int lb=st[b];
    int rb=lb+cnt[b];

    long long ans=0;
    int p=lb;

    // 统计 tin[y] <= tout[x]
    for(int i=la;i<ra;i++){
        while(p<rb&&ptin[p]<=pout[i])
            p++;

        ans+=p-lb;
    }

    p=lb;

    // 减去 tin[y] <= tin[x]
    for(int i=la;i<ra;i++){
        while(p<rb&&ptin[p]<=ptin[i])
            p++;

        ans-=p-lb;
    }

    return ans;
}

long long calcBinary(int a,int b){
    int sa=cnt[a];
    int sb=cnt[b];

    int la=st[a];
    int ra=la+sa;
    int lb=st[b];
    int rb=lb+sb;

    long long ans=0;

    if(sa<=sb){
        for(int i=la;i<ra;i++){
            int t=ptin[i];
            int x=ord[t];

            int l=upper_bound(ptin+lb,ptin+rb,t)-ptin;
            int r=upper_bound(ptin+lb,ptin+rb,out[x])-ptin;

            ans+=r-l;
        }
    }
    else{
        for(int i=lb;i<rb;i++){
            int t=ptin[i];

            int x=lower_bound(ptin+la,ptin+ra,t)-ptin-la;
            int y=lower_bound(pout+la,pout+ra,t)-pout-la;

            ans+=x-y;
        }
    }

    return ans;
}

int calcSmall(int a,int b){
    int sa=cnt[a];
    int sb=cnt[b];

    if(sa==0||sb==0)
        return 0;

    int mn=min(sa,sb);
    int mx=max(sa,sb);
    int lg=32-__builtin_clz(mx);

    long long ans;

    if(sa+sb<=2*mn*lg)
        ans=calcMerge(a,b);
    else
        ans=calcBinary(a,b);

    return ans>=INF?INF:ans;
}

inline int hashPos(unsigned int key){
    unsigned int p=key*2654435761u&HMASK;

    while(hkey[p]&&hkey[p]!=key)
        p=(p+1)&HMASK;

    return p;
}

int query(int a,int b){
    if(hid[a])
        return f[hid[a]][b];

    if(hid[b])
        return g[hid[b]][a];

    unsigned int key=((unsigned int)a<<15)|b;
    int p=hashPos(key);

    if(hkey[p])
        return hval[p];

    int ans=calcSmall(a,b);

    hkey[p]=key;
    hval[p]=ans;

    return ans;
}

int main(){
    n=read();
    R=read();
    q=read();

    col[1]=read();
    cnt[col[1]]++;

    for(int i=2;i<=n;i++){
        fa[i]=read();
        col[i]=read();

        cnt[col[i]]++;

        nxt[i]=head[fa[i]];
        head[fa[i]]=i;
    }

    dfs(1);

    st[1]=1;

    for(int i=2;i<=R;i++)
        st[i]=st[i-1]+cnt[i-1];

    for(int i=1;i<=R;i++)
        cur[i]=st[i];

    // 按地区保存所有节点的DFS序
    for(int t=1;t<=n;t++){
        int x=ord[t];
        ptin[cur[col[x]]++]=t;
    }

    for(int i=1;i<=R;i++)
        cur[i]=st[i];

    // 按地区保存所有节点的子树右端点
    for(int x=1;x<=n;x++)
        pout[cur[col[x]]++]=out[x];

    for(int i=1;i<=R;i++)
        sort(pout+st[i],pout+st[i]+cnt[i]);

    for(int i=1;i<=R;i++){
        if(cnt[i]>=B){
            hid[i]=++hcnt;
            hreg[hcnt]=i;
        }
    }

    for(int i=1;i<=hcnt;i++)
        buildHeavy(i);

    while(q--){
        int a=read();
        int b=read();

        printf("%d\n",query(a,b));
        fflush(stdout);
    }

    return 0;
}