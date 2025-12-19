#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 1e6+5;
const int MAXH = 20;
const int MAXP = 1340;
const int LIMIT = 11000;

int n,q,m;
int val[MAXN];

int bigprime[MAXN];
bitset<MAXP>smallprime[MAXN];
bitset<MAXP>fromtop[MAXN];
int sorted[MAXN];

int cntp;
int primes[MAXP];
int minprime[MAXM];

bool vis[MAXN];
int cnt[MAXN];
int kind;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

struct Query{
    int l,r,u,v,lca,id;
};
Query query[MAXN];
int ans[MAXN];

int dep[MAXN];
int seg[MAXN << 1];
int st[MAXN];
int ed[MAXN];
int stjump[MAXN][MAXH];
int cntd;

bitset<MAXP>tree[MAXN<<2];

int sz[MAXN];
int son[MAXN];
int dfn[MAXN];
int top[MAXN];
int dfnseg[MAXN];
int dfncnt;

int blen;
int bi[MAXN<<1];

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

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

void euler(int n){
    for(int i=2;i<=n;i++){
        if(minprime[i]==0){
            primes[++cntp]=i;
            minprime[i]=cntp;
        }
        for(int j=1;j<=cntp&&i*primes[j]<=n;j++){
            minprime[i*primes[j]]=j;
            if(i%primes[j]==0){
                break;
            }
        }
    }
}

void compute1(int val,int i){
    for(int p=minprime[val];val!=1;p=minprime[val]){
        smallprime[i].set(p-1);
        while(val%primes[p]==0){
            val/=primes[p];
        }
    }
}

void compute2(int val,int i){
    for(int p=1;p<=cntp;p++){
        if(val%primes[p]==0){
            smallprime[i].set(p-1);
            while(val%primes[p]==0){
                val/=primes[p];
            }
            if(val<=LIMIT){
                compute1(val,i);
            }
        }
    }
}

long long mul(long long a, long long b, long long mod) {
    return a * b % mod;
}

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = mul(res, base, mod);
        base = mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

bool is_prime(long long n) {
    if (n < 2) return false;
    // 固定的基数，对 long long 范围内的数是确定性的
    long long prm[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    // 试除
    for (long long p : prm) {
        if (n == p) return true; // n 本身就是小质数
        if (n % p == 0) return false; // n 是小质数的倍数
    }

    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (long long a : prm) { // a是基数
        long long x = power(a, d, n);
        long long y = 0;
        for (int j = 0; j < s; ++j) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) return false; // 二次探测
            x = y;
        }
        // 经过所有平方后，x = a^(n-1) mod n。如果n是质数，x必须为1。
        if (x != 1) return false;
    }
    return true;
}

map<long long, int> factors;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long gcd(long long a,long long b){
	long long az=__builtin_ctz(a);
	long long bz=__builtin_ctz(b);
	long long z=min(az,bz);b>>=bz;
	while(a){
		a>>=az;long long diff=a-b;
		az=__builtin_ctz(diff),b=min(a,b),a=abs(diff);
	}
	return b<<z;
} 

long long pollard_rho(long long n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;
    
    // 使用 mt19937_64 提升随机性
    long long c = uniform_int_distribution<long long>(1, n - 1)(rng);
    long long x = uniform_int_distribution<long long>(0, n - 1)(rng);
    long long y = x;
    long long d = 1;

    while (d == 1) {
        x = (mul(x, x, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        d = gcd(abs(x - y), n);
        // 如果失败，换个c再试
        if (d == n) {
            c = uniform_int_distribution<long long>(1, n - 1)(rng);
            x = uniform_int_distribution<long long>(0, n - 1)(rng);
            y = x;
            d = 1;
        }
    }
    return d;
}

void find_factors(long long n) {
    if (n == 1) return;
    if (is_prime(n)) {
        factors[n]++;
        return;
    }
    long long p = pollard_rho(n);
    find_factors(p);
    find_factors(n / p);
}

int max_prime(int n){
    if(is_prime(n)) return n;
    else{
        factors.clear();
        find_factors(n);
        long long max_fator=0;
        for(auto const& [p, a] : factors)
            max_fator=max(max_fator,p); 
        return max_fator;
    }
}

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    seg[++cntd] = u;
    st[u] = cntd;
    stjump[u][0] = fa;
    sz[u]=1;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa) {
            dfs(v, u);
            sz[u]+=sz[v];
            if(son[u]==0||sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
    seg[++cntd] = u;
    ed[u] = cntd;
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    dfnseg[dfncnt]=u;
    if(son[u]){
        fromtop[son[u]]=fromtop[u]|smallprime[son[u]];
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=stjump[u][0]&&v!=son[u]){
            fromtop[v]=smallprime[v];
            dfs2(v,v);
        }
    }
}

bool cmp(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if ((bi[a.l] & 1) == 1) {
        return a.r < b.r;
    } else {
        return a.r > b.r;
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) {
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=smallprime[dfnseg[l]];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=(tree[i<<1]|tree[i<<1|1]);
    }
}

bitset<MAXP>querytree(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid&&jobr>mid){
            return (querytree(jobl,jobr,l,mid,i<<1)|querytree(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return querytree(jobl,jobr,l,mid,i<<1);
        }
        else{
            return querytree(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

bitset<MAXP>querypath(int x,int y){
    bitset<MAXP>ans;
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            ans|=fromtop[y];
            y = stjump[top[y]][0];
        } else {
            ans|=fromtop[x];
            x = stjump[top[x]][0];
        }
    }
    ans|=querytree(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1);
    return ans;
}

int findfac(int val){
    int l=1,r=cntp,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(primes[mid]>=val){
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
        if(val[i]<=LIMIT){
            compute1(val[i],i);
        }
        else{
            int fac=max_prime(val[i]);
            if(fac>LIMIT){
                bigprime[i]=fac;
                val[i]/=fac;
            }
            else{
                int p=findfac(fac);
                smallprime[i].set(p-1);
                while(val[i]%fac==0){
                    val[i]/=fac;
                }
            }
            if(val[i]<LIMIT){
                compute1(val[i],i);
            }
            else{
                compute2(val[i],i);
            }
        }
    }
    for(int i=1;i<=n;i++){
        sorted[i]=bigprime[i];
    }
    sorted[n+1]=0;
    sort(sorted+1,sorted+n+2);
    m=1;
    for(int i=2;i<=n+1;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++m]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        bigprime[i]=find(bigprime[i]);
    }
    dfs(1,0);
    fromtop[1]=smallprime[1];
    dfs2(1,1);
    build(1,n,1);
    blen=sqrt(cntd);
    // blen=max(1,(int)pow(cntd,3.0/2));
    for(int i=1;i<=cntd;i++){
        bi[i]=(i-1)/blen+1;
    }
}

void invert(int node) {
    int val = bigprime[node];
    if(val==1){
        return ;
    }
    if (vis[node]) {
        if (--cnt[val] == 0) {
            kind--;
        }
    } else {
        if (++cnt[val] == 1) {
            kind++;
        }
    }
    vis[node] = !vis[node];
}

void compute() {
    int winl = 1, winr = 0;
    for (int i = 1; i <= q; i++) {
        int jobl = query[i].l;
        int jobr = query[i].r;
        int lca = query[i].lca;
        int id = query[i].id;
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
        if (lca > 0) {
            invert(lca);
        }
        ans[id] = kind;
        if (lca > 0) {
            invert(lca);
        }
        ans[id]+=querypath(query[i].u,query[i].v).count();
    }
}

int main()
{
    euler(LIMIT);
    // cout<<cntp<<endl;
    n=read(),q=read();
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
    for (int i = 1, u, v, uvlca; i <= q; i++) {
        u=read(),v=read();
        if (st[v] < st[u]) {
            swap(u, v);
        }
        uvlca = lca(u, v);
        if (u == uvlca) {
            query[i].l = st[u];
            query[i].r = st[v];
            query[i].lca = 0;
        } else {
            query[i].l = ed[u];
            query[i].r = st[v];
            query[i].lca = uvlca;
        }
        query[i].u=u,query[i].v=v;
        query[i].id = i;
    }
    sort(query+1,query+q+1,cmp);
    compute();
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}