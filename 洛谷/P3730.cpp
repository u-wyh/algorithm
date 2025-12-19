#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 401;

int n,q,m;
int val[MAXN];
int arr[MAXN];

struct node{
    int l,r,k,id;
};
node nums[MAXN];
int ans[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

// 记录这个块中总个数是多少
int block[MAXB];
// 表示种类i的个数  即热度
int cnt1[MAXN];
// 表示为这个热度值的有几个种类
int cnt2[MAXN];
// 全局总共有多少个种类
int all;

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
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(i*blen,n);
    }

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

    sort(nums+1,nums+1+q,cmp);
}

void add(int val){
    cnt2[cnt1[val]]--;
    block[bi[cnt1[val]]]--;
    cnt1[val]++;
    if(cnt1[val]==1){
        all++;
    }
    cnt2[cnt1[val]]++;
    block[bi[cnt1[val]]]++;
}

void del(int val){
    cnt2[cnt1[val]]--;
    block[bi[cnt1[val]]]--;
    cnt1[val]--;
    if(cnt1[val]==0){
        all--;
    }
    else{
        cnt2[cnt1[val]]++;
        block[bi[cnt1[val]]]++;
    }
}

int query(int k){
    if(k>all){
        return -1;
    }
    int b=1;
    for(int i=1;i<=bnum;i++){
        if(k<=block[i]){
            b=i;
            break;
        }
        k-=block[i];
    }
    for(int i=bl[b];i<=br[b];i++){
        if(k<=cnt2[i]){
            return i;
        }
        k-=cnt2[i];
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=q;i++){
        nums[i].l=read(),nums[i].r=read(),nums[i].k=read();
        nums[i].id=i;
    }
    prepare();
    int winl=1,winr=0;
    for(int i=1;i<=q;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobk=nums[i].k;
        int jobi=nums[i].id;
        while(jobl<winl){
            add(val[--winl]);
        }
        while(jobl>winl){
            del(val[winl++]);
        }
        while(jobr>winr){
            add(val[++winr]);
        }
        while(jobr<winr){
            del(val[winr--]);
        }
        ans[jobi]=query(jobk);
    }
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}