#include<bits/stdc++.h>
using namespace std;
const int BASE = 13131;
const int MOD = 1e9+7;
const int MAXN = 3e6+5;
const int MAXM = 1e5+5;

int n,q,m,k;
int len;
char s[MAXN];

long long p[MAXN];
long long h[MAXN];

long long val[MAXN];
long long sorted[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXM];
int cntq;

int cnt[MAXN];
long long curans;
long long ans[MAXM];

int blen;
int bi[MAXN];

int find(long long val){
    int l=1,r=m,ans=1;
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

bool cmp(node &a,node &b){
    if(bi[a.l]==bi[b.l]){
        if(bi[a.l]&1){
            return a.r<b.r;
        }
        else{
            return a.r>b.r;
        }
    }
    return a.l<b.l;
}

void prepare(){
    p[0]=1;
    for(int i=1;i<=n;i++){
        // p[i]=(p[i-1]*BASE)%MOD;
        p[i]=p[i-1]*BASE;
    }
    for(int i=1;i<=n;i++){
        // h[i]=(h[i-1]*BASE+s[i]-'a'+1)%MOD;
        h[i]=h[i-1]*BASE+s[i]-'a'+1;
    }
    for(int l=1,r=k;l<=len;l++,r++){
        // val[l]=(h[r]-((h[l-1]*p[k])%MOD)+MOD)%MOD;
        val[l]=h[r]-h[l-1]*p[k];
        sorted[l]=val[l];
    }
    sort(sorted+1,sorted+len+1);
    m=1;
    for(int i=2;i<=len;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++m]=sorted[i];
        }
    }
    for(int i=1;i<=len;i++){
        val[i]=find(val[i]);
    }
    blen=max(1,(int)((double)n/sqrt(cntq)));
    for(int i=1;i<=len;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(nums+1,nums+cntq+1,cmp);
}

void add(long long val){
    curans+=cnt[val];
    cnt[val]++;
}

void del(long long val){
    cnt[val]--;
    curans-=cnt[val];
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=cntq;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobi=nums[i].id;
        while(winl>jobl){
            add(val[--winl]);
        }
        while(winl<jobl){
            del(val[winl++]);
        }
        while(winr<jobr){
            add(val[++winr]);
        }
        while(winr>jobr){
            del(val[winr--]);
        }
        ans[jobi]=curans;
    }
}

int main()
{
    scanf("%d %d %d",&n,&q,&k);
    scanf("%s",s+1);
    len=n-k+1;
    cntq=0;
    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if(l<=len){
            ++cntq;
            nums[cntq]={l,min(r,len),i};
        }
    }
    prepare();
    compute();
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}