#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e6+5;
const int BIT = 16;

int n,m,T;

int val[MAXN];

int op[MAXN];
int s[MAXN];
int v[MAXN];
int sl[MAXN];
int sr[MAXN];
int x[MAXN];
int d[MAXN];
int t[MAXN];

int root[MAXN];
int tree[MAXM][2];
int pass[MAXM];
int cntt;

int headp[MAXN<<2];
int nxtp[MAXM];
int top[MAXM];
int cntp=1;

int headb[MAXN<<2];
int nxtb[MAXM];
int tob[MAXM];
int cntb=1;

struct Product {
    int s, v;
};
bool cmp(Product a, Product b) {
    return a.s < b.s;
}

Product product[MAXN];
int ans[MAXN];

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

int insert(int val,int i){
    int rt=++cntt;
    tree[rt][0]=tree[i][0];
    tree[rt][1]=tree[i][1];
    pass[rt]=pass[i]+1;
    for(int b=BIT,pre=rt,cur;b>=0;b--,pre=cur){
        int path=(val>>b)&1;
        i=tree[i][path];
        cur=++cntt;
        tree[cur][0]=tree[i][0];
        tree[cur][1]=tree[i][1];
        pass[cur]=pass[i]+1;
        tree[pre][path]=cur;
    }
    return rt;
}

int query(int val,int u,int v){
    int ans=0;
    for(int b=BIT;b>=0;b--){
        int path=(val>>b)&1;
        int best=path^1;
        if(pass[tree[v][best]]>pass[tree[u][best]]){
            ans+=(1<<b);
            u=tree[u][best];
            v=tree[v][best];
        }
        else{
            u=tree[u][path];
            v=tree[v][path];
        }
    }
    return ans;
}

void addp(int u,int v){
    nxtp[cntp]=headp[u];
    top[cntp]=v;
    headp[u]=cntp++;
}

void addproduct(int jobi,int pi,int l,int r,int i){
    addp(i,pi);
    if(l<r){
        int mid=(l+r)>>1;
        if(jobi<=mid){
            addproduct(jobi,pi,l,mid,i<<1);
        }
        else{
            addproduct(jobi,pi,mid+1,r,i<<1|1);
        }
    }
}

void addb(int u,int v){
    nxtb[cntb]=headb[u];
    tob[cntb]=v;
    headb[u]=cntb++;
}

void addbuy(int jobl,int jobr,int jobi,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addb(i,jobi);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            addbuy(jobl,jobr,jobi,l,mid,i<<1);
        }
        if(jobr>mid){
            addbuy(jobl,jobr,jobi,mid+1,r,i<<1|1);
        }
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        root[i]=insert(val[i],root[i-1]);
    }
    for(int i=1;i<=m;i++){
        if(op[i]==0){
            addproduct(t[i],i,1,T,1);
        }
        else{
            ans[i]=query(x[i],root[sl[i]-1],root[sr[i]]);
            int st=max(t[i]-d[i]+1,1);
            if(st<=t[i]){
                addbuy(st,t[i],i,1,T,1);
            }
        }
    }
}

int lower(int size, int num) {
    int l = 1, r = size, ansv = size + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (product[mid].s >= num) {
            ansv = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ansv;
}

int upper(int size, int num) {
    int l = 1, r = size, ansv = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (product[mid].s <= num) {
            ansv = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ansv;
}

void dfs(int l,int r,int i){
    int pcnt=0;
    for(int ei=headp[i];ei;ei=nxtp[ei]){
        product[++pcnt]={s[top[ei]],v[top[ei]]};
    }
    sort(product+1,product+pcnt+1,cmp);
    cntt=0;
    for(int k=1;k<=pcnt;k++){
        root[k]=insert(product[k].v,root[k-1]);
    }
    for (int e = headb[i], id, pre, post; e > 0; e = nxtb[e]) {
        id = tob[e];
        pre = lower(pcnt, sl[id]) - 1;
        post = upper(pcnt, sr[id]);
        ans[id] = max(ans[id], query(x[id], root[pre], root[post]));
    }
    if (l < r) {
        int mid = (l + r) >> 1;
        dfs(l, mid, i << 1);
        dfs(mid + 1, r, i << 1 | 1);
    }
}

int main()
{
    n=read(),m=read();
    T=0;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        op[i]=read();
        if(op[i]==0){
            T++;
            s[i]=read(),v[i]=read();
        }
        else{
            sl[i]=read(),sr[i]=read(),x[i]=read(),d[i]=read();
        }
        t[i]=T;
    }
    prepare();
    dfs(1,T,1);
    for(int i=1;i<=m;i++){
        if(op[i]==1){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}