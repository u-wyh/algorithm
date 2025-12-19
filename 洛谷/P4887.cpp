#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1<<14;

int n,m,k;
int val[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];
long long ans[MAXN];

int blen;
int bi[MAXN];

int one[MAXM];
int kone[MAXM];
int cntk;

int headl[MAXN];
int headr[MAXN];
int nxtq[MAXN<<1];
int ql[MAXN<<1];
int qr[MAXN<<1];
int qop[MAXN<<1];
int qid[MAXN<<1];
int cntq=1;

int cnt[MAXM];

long long pre[MAXN];
long long suf[MAXN];

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
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(nums+1,nums+m+1,cmp);
    one[0]=0;
    if(k==0){
        kone[++cntk]=0;
        return ;
    }
    for(int i=1;i<MAXM;i++){
        one[i]=one[i-(i&-i)]+1;
        if(one[i]==k){
            kone[++cntk]=i;
        }
    }
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

void compute(){
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+cnt[val[i]];
        for(int j=1;j<=cntk;j++){
            cnt[val[i]^kone[j]]++;
        }
    }
    for(int i=0;i<MAXM;i++){
        cnt[i]=0;
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1]+cnt[val[i]];
        for(int j=1;j<=cntk;j++){
            cnt[val[i]^kone[j]]++;
        }
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

    for(int i=0;i<MAXM;i++){
        cnt[i]=0;
    }
    for(int x=1;x<=n;x++){
        for(int i=1;i<=cntk;i++){
            cnt[val[x]^kone[i]]++;
        }
        for(int i=headl[x];i;i=nxtq[i]){
            int l=ql[i],r=qr[i],op=qop[i],id=qid[i];
            for(int j=l;j<=r;j++){
                ans[id]+=1ll*op*cnt[val[j]];
            }
        }
    }
    
    for(int i=0;i<MAXM;i++){
        cnt[i]=0;
    }
    for(int x=n;x>0;x--){
        for(int i=1;i<=cntk;i++){
            cnt[val[x]^kone[i]]++;
        }
        for(int i=headr[x];i;i=nxtq[i]){
            int l=ql[i],r=qr[i],op=qop[i],id=qid[i];
            for(int j=l;j<=r;j++){
                ans[id]+=1ll*op*cnt[val[j]];
            }
        }
    }
}

int main()
{
    n=read(),m=read(),k=read();
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
        printf("%lld\n",ans[i]);
    }
    return 0;
}