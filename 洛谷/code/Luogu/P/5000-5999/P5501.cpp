#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e5+5;
const int MAXB = 405;

int n,m;
int val[MAXN];
long long presum[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

struct node{
    int l,r,id;
};
node nums[MAXN];

int headq[MAXN];
int nxtq[MAXN<<1];
int ql[MAXN<<1];
int qr[MAXN<<1];
int qop[MAXN<<1];
int qid[MAXN<<1];
int cntq=1;

long long treecnt[MAXM];
long long treesum[MAXM];
long long pre[MAXN];

int blocklesscnt[MAXB];
int numlesscnt[MAXM];
long long blockmoresum[MAXB];
long long nummoresum[MAXM];

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
        presum[i]=presum[i-1]+val[i];
    }

    blen=sqrt(MAXM-1);
    bnum=(MAXM+blen-2)/blen;
    for(int i=1;i<MAXM;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(MAXM-1,i*blen);
    }

    sort(nums+1,nums+m+1,cmp);
}

inline int lowbit(int x){
    return x&-x;
}

void add(long long *tree,int x,int v){
    while(x<MAXM){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

long long sum(long long *tree,int x){
    long long ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void addleftoffline(int x,int l,int r,int op,int id){
    nxtq[cntq]=headq[x];
    ql[cntq]=l;
    qr[cntq]=r;
    qop[cntq]=op;
    qid[cntq]=id;
    headq[x]=cntq++;
}

void addval(int val){
    for(int b=bi[val]+1;b<=bi[MAXM-1];b++){
        blocklesscnt[b]++;
    }
    for(int i=val+1;i<=br[bi[val]];i++){
        numlesscnt[i]++;
    }
    for(int b=1;b<=bi[val]-1;b++){
        blockmoresum[b]+=val;
    }
    for(int i=bl[bi[val]];i<val;i++){
        nummoresum[i]+=val;
    }
}

int lesscnt(int x){
    return blocklesscnt[bi[x]]+numlesscnt[x];
}

long long moresum(int x){
    return blockmoresum[bi[x]]+nummoresum[x];
}

void compute(){
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+(1ll*val[i]*sum(treecnt,val[i]-1))+(presum[i-1]-sum(treesum,val[i]));
        add(treecnt,val[i],1);
        add(treesum,val[i],val[i]);
    }
    
    int winl=1,winr=0;
    for(int i=1;i<=m;i++){
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
            addleftoffline(winr,jobl,winl-1,1,jobi);
            ans[jobi]-=pre[winl-1]-pre[jobl-1];
        }
        if(winl<jobl){
            addleftoffline(winr,winl,jobl-1,-1,jobi);
            ans[jobi]-=pre[winl-1]-pre[jobl-1];
        }
        winl=jobl;
    }

    long long tmp;
    for(int x=1;x<=n;x++){
        addval(val[x]);
        for(int i=headq[x];i;i=nxtq[i]){
            int l=ql[i],r=qr[i],op=qop[i],id=qid[i];
            for(int j=l;j<=r;j++){
                tmp=1ll*lesscnt(val[j])*val[j]+moresum(val[j]);
                if(op==1){
                    ans[id]+=tmp;
                }
                else{
                    ans[id]-=tmp;
                }
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    prepare();
    compute();
    for(int i=2;i<=m;i++){
        ans[nums[i].id]+=ans[nums[i-1].id];
    }
    for(int i=1;i<=m;i++){
        ans[nums[i].id]+=presum[nums[i].r]-presum[nums[i].l-1];
    }
    for(int i=1;i<=m;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}