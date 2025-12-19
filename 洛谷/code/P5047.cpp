#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,q,m;
int val[MAXN];
int arr[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];
int headl[MAXN];
int headr[MAXN];
int nxtq[MAXN<<1];
int ql[MAXN<<1];
int qr[MAXN<<1];
int qop[MAXN<<1];
int qid[MAXN<<1];
int cntq=1;

int blen,bnum;
int bi[MAXN];
int bl[MAXN];
int br[MAXN];

int tree[MAXN];
long long pre[MAXN];
long long suf[MAXN];

long long blockcnt[MAXB];
long long numcnt[MAXN];

long long ans[MAXN];

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

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool cmp(node &a, node &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if ((bi[a.l] & 1) == 1) {
        return a.r < b.r;
    } else {
        return a.r > b.r;
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(i*blen,m);
    }
    sort(nums+1,nums+q+1,cmp);
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=m){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void addleftoffline(int x,int l,int r,int op,int id){
    nxtq[cntq]=headl[x];
    ql[cntq]=l;
    qr[cntq]=r;
    qop[cntq]=op;
    qid[cntq]=id;
    headl[x]=cntq++;
}

void addrightoffline(int x,int l,int r,int op,int id){
    nxtq[cntq]=headr[x];
    ql[cntq]=l;
    qr[cntq]=r;
    qop[cntq]=op;
    qid[cntq]=id;
    headr[x]=cntq++;
}

void addleftcnt(int val){
    for(int b=1;b<=bi[val]-1;b++){
        blockcnt[b]++;
    }
    for(int i=bl[bi[val]];i<val;i++){
        numcnt[i]++;
    }
}

void addrightcnt(int val){
    for(int b=bi[val]+1;b<=bi[m];b++){
        blockcnt[b]++;
    }
    for(int i=val+1;i<=br[bi[val]];i++){
        numcnt[i]++;
    }
}

long long getcnt(int val){
    return blockcnt[bi[val]]+numcnt[val];
}

void compute(){
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+i-1-sum(val[i]);
        add(val[i],1);
    }
    for(int i=1;i<=m;i++){
        tree[i]=0;
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1]+sum(val[i]-1);
        add(val[i],1);
    }

    int winl=1,winr=0;
    for(int i=1;i<=q;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobi=nums[i].id;
        if(winr<jobr){
            if(winl>1){
                addleftoffline(winl-1,winr+1,jobr,-1,jobi);
            }
            ans[jobi]+=pre[jobr]-pre[winr];
        }
        if(winr>jobr){
            if(winl>1){
                addleftoffline(winl-1,jobr+1,winr,1,jobi);
            }
            ans[jobi]+=pre[jobr]-pre[winr];
        }
        winr=jobr;
        if(winl>jobl){
            if(winr<n){
                addrightoffline(winr+1,jobl,winl-1,-1,jobi);
            }
            ans[jobi]+=suf[jobl]-suf[winl];
        }
        if(winl<jobl){
            if(winr<n){
                addrightoffline(winr+1,winl,jobl-1,1,jobi);
            }
            ans[jobi]+=suf[jobl]-suf[winl];
        }
        winl=jobl;
    }

    for(int x=1;x<=n;x++){
        addleftcnt(val[x]);
        for(int i=headl[x];i;i=nxtq[i]){
            int l=ql[i],r=qr[i],op=qop[i],id=qid[i];
            for(int j=l;j<=r;j++){
                ans[id]+=1ll*op*getcnt(val[j]);
            }
        }
    }

    for(int i=1;i<=bnum;i++){
        blockcnt[i]=0;
    }
    for(int i=1;i<=m;i++){
        numcnt[i]=0;
    }
    for(int x=n;x>=1;x--){
        addrightcnt(val[x]);
        for(int i=headr[x];i;i=nxtq[i]){
            int l=ql[i],r=qr[i],op=qop[i],id=qid[i];
            for(int j=l;j<=r;j++){
                ans[id]+=1ll*op*getcnt(val[j]);
            }
        }
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=q;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    prepare();
    compute();
    for(int i=2;i<=q;i++){
        ans[nums[i].id]+=ans[nums[i-1].id];
    }
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}