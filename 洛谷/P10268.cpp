#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXB = 505;
const int MOD = 1e9+7;

int n,m,q;
int val[MAXN];
int curans;
int res,inv;

struct Edge{
    int u,v;
};
Edge edge[MAXM];

struct Query{
    int l,r,id;
};
Query query[MAXN];
int ans[MAXN];

int blen,bnum;
int bi[MAXM];
int bl[MAXB];
int br[MAXB];

int fa[MAXN];
int all[MAXN];
int sz[MAXN];

int rollback[MAXM][4];
int top;

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

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

bool cmp(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    return a.r < b.r;
}

void prepare(){
    blen=sqrt(m);
    bnum=(m+blen-1)/blen;
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(m,i*blen);
    }
    sort(query+1,query+q+1,cmp);
}

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void undo(){
    int fx=rollback[top][0];
    int fy=rollback[top][1];
    fa[fy]=fy;
    all[fx]-=rollback[top][2];
    all[fx]%=MOD;
    sz[fx]-=rollback[top][3];
    curans=(curans-(2*all[fx]*all[fy]%MOD)+MOD)%MOD;
}

void force(int l,int r){
    for(int i=l;i<=r;i++){
        int x=edge[i].u;
        int y=edge[i].v;
        int fx=find(x),fy=find(y);
        if(fx!=fy){
            if(sz[fx]<sz[fy]){
                swap(fx,fy);
            }
            fa[fy]=fx;
            sz[fx]+=sz[fy];
            curans=(curans+2*all[fx]*all[fy]%MOD)%MOD;
            all[fx]+=all[fy];
            all[fx]%=MOD;

            top++;
            rollback[top][0]=fx;
            rollback[top][1]=fy;
            rollback[top][2]=all[fy];
            rollback[top][3]=sz[fy];
        }
    }
}

void addright(int i){
    int x=edge[i].u;
    int y=edge[i].v;
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        if(sz[fx]<sz[fy]){
            swap(fx,fy);
        }
        fa[fy]=fx;
        sz[fx]+=sz[fy];
        curans=(curans+2*all[fx]*all[fy]%MOD)%MOD;
        all[fx]+=all[fy];
        all[fx]%=MOD;
    }
}

void addleft(int i){
    int x=edge[i].u;
    int y=edge[i].v;
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        if(sz[fx]<sz[fy]){
            swap(fx,fy);
        }
        fa[fy]=fx;
        sz[fx]+=sz[fy];
        curans=(curans+2*all[fx]*all[fy]%MOD)%MOD;
        all[fx]+=all[fy];
        all[fx]%=MOD;
            
        top++;
        rollback[top][0]=fx;
        rollback[top][1]=fy;
        rollback[top][2]=all[fy];
        rollback[top][3]=sz[fy];
    }
}

void compute(){
    for(int b=1,qi=1;b<=bnum&&qi<=q;b++){
        curans=res;
        // top=0;
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
            all[i]=val[i];
        }
        int winl=br[b]+1,winr=br[b];
        for(;qi<=q&&bi[query[qi].l]==b;qi++){
            int jobl=query[qi].l;
            int jobr=query[qi].r;
            int id=query[qi].id;
            if(jobr<=br[b]){
                force(jobl,jobr);
                ans[id]=curans;
                while(top){
                    undo();
                    top--;
                }
            }
            else{
                while (winr < jobr) {
                    addright(++winr);
                }
                while (winl > jobl) {
                    addleft(--winl);
                }
                ans[id] = curans;
                while(top){
                    undo();
                    top--;
                }
                winl=br[b]+1;
            }
        }
    }
}

signed main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        edge[i].u=read(),edge[i].v=read();
    }
    for(int i=1;i<=q;i++){
        query[i].l=read();
        query[i].r=read();
        query[i].id=i;
    }

    inv=power((n*(n-1))%MOD,MOD-2);
    res=0;
    for(int i=1;i<=n;i++){
        res=((res+val[i]*val[i]%MOD)%MOD+MOD)%MOD;
    }

    prepare();
    compute();
    
    for(int i=1;i<=q;i++){
        ans[i]=((((ans[i]-res+MOD)%MOD)*inv)%MOD+MOD)%MOD;
    }
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}