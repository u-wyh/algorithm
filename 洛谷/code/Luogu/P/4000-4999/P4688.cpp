#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = 3e4+5;

int n,m;
int val[MAXN];
int sorted[MAXN];

int blen;
int bi[MAXN];

int cnt[MAXN];
bitset<MAXN>curset;
bool hasset[MAXT];
bitset<MAXN>bs[MAXT];

struct node{
    int l,r,id;
};
node nums[MAXT*3];
int ans[MAXT];

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

bool cmp(node &a,node &b){
    if(bi[a.l]==bi[b.l]){;
        if(bi[a.l]&1){
            return a.r<b.r;
        }
        else{
            return a.r>b.r;
        }
    }
    return a.l<b.l;
}

int find(int val){
    int l=1,r=n,ans=1;
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

void prepare(){
    for(int i=1;i<=n;i++){
        sorted[i]=val[i];
    }
    sort(sorted+1,sorted+n+1);
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
}

void add(int x) {
    cnt[x]++;
    curset[x + cnt[x] - 1] = 1;
}

void del(int x) {
    cnt[x]--;
    curset[x + cnt[x]] = 0;
}

void compute(int q){
    int winl = 1, winr = 0;
    for (int i = 1; i <= q; i++) {
        int jobl = nums[i].l;
        int jobr = nums[i].r;
        int id = nums[i].id;
        while (winl > jobl) {
            add(val[--winl]);
        }
        while (winr < jobr) {
            add(val[++winr]);
        }
        while (winl < jobl) {
            del(val[winl++]);
        }
        while (winr > jobr) {
            del(val[winr--]);
        }
        if (!hasset[id]) {
            hasset[id] = true;
            bs[id] = curset;
        } else {
            bs[id] &= curset;
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    for(int t=MAXT-1;m>0;m-=t){
        int k=min(m,t);
        memset(cnt,0,sizeof(cnt));
        memset(hasset,0,sizeof(hasset));
        memset(ans,0,sizeof(ans));
        curset.reset();
        int cntq=0,l,r;
        for(int i=1;i<=k;i++){
            for(int j=1;j<=3;j++){
                l=read(),r=read();
                nums[++cntq]={l,r,i};
                ans[i]+=r-l+1;
            }
        }
        sort(nums+1,nums+cntq+1,cmp);
        compute(cntq);
        for(int i=1;i<=k;i++){
            ans[i]-=bs[i].count()*3;
        }
        for(int i=1;i<=k;i++){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}