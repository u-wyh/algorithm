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

int blen,bnum;
int bi[MAXN];
int br[MAXB];

int cnt[MAXN];
long long curans;

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

bool cmp(node &a,node &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    return a.r<b.r;
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
        br[i]=min(n,i*blen);
    }
    sort(nums+1,nums+q+1,cmp);
}

long long force(int l,int r){
    long long res=0;
    for(int i=l;i<=r;i++){
        cnt[val[i]]++;
    }
    for(int i=l;i<=r;i++){
        res=max(res,1ll*cnt[val[i]]*arr[val[i]]);
    }
    for(int i=l;i<=r;i++){
        cnt[val[i]]--;
    }
    return res;
}

void add(int val){
    cnt[val]++;
    curans=max(curans,1ll*cnt[val]*arr[val]);
}

void del(int val){
    cnt[val]--;
}

void compute(){
    for(int b=1,qi=1;b<=bnum&&qi<=q;b++){
        curans=0;
        for(int i=1;i<=m;i++){
            cnt[i]=0;
        }
        int winl=br[b]+1,winr=br[b];
        for(;qi<=q&&bi[nums[qi].l]==b;qi++){
            int jobl=nums[qi].l;
            int jobr=nums[qi].r;
            int jobi=nums[qi].id;
            if(jobr<=br[b]){
                ans[jobi]=force(jobl,jobr);
            }
            else{
                while(winr<jobr){
                    add(val[++winr]);
                }
                long long backup=curans;
                while(winl>jobl){
                    add(val[--winl]);
                }
                ans[jobi]=curans;
                curans=backup;
                while(winl<=br[b]){
                    del(val[winl++]);
                }
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
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}