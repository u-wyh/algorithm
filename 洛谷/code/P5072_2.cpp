#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m;
int val[MAXN];
int len;
int sortv[MAXN];

struct node{
    int l,r,p,id;
};
node nums[MAXN];
long long ans[MAXN];

int blen;
int bi[MAXN];

int d;
long long bigpower[MAXB];
long long smlpower[MAXB];

int head;
int cnt[MAXN];
long long sum[MAXN];
int suf[MAXN];
int pre[MAXN];

bool cmp(node &a,node &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    if(bi[a.l]&1){
        return a.r>b.r;
    }
    else{
        return a.r<b.r;
    }
}

inline int find(int val){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sortv[mid]>=val){
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
    for(int i=1;i<=n;i++){
        bi[i]=(i-1+blen)/blen;
    }

    for(int i=1;i<=n;i++){
        sortv[i]=val[i];
    }
    sort(sortv+1,sortv+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sortv[i]!=sortv[i-1]){
            sortv[++len]=sortv[i];
        }
    }

    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    sort(nums+1,nums+m+1,cmp);
}

inline void calc(int p,int len){
    d=sqrt(len);
    smlpower[0]=1;
    for(int i=1;i<=d;i++){
        smlpower[i]=(smlpower[i-1]<<1)%p;
    }
    bigpower[0]=1;
    for(int i=1;i<=len/d;i++){
        bigpower[i]=(bigpower[i-1]*smlpower[d])%p;
    }
}

inline void deleteval(int val){
    if(val==head){
        head=suf[head];
        pre[head]=0;
        suf[val]=0;
    }
    else{
        suf[pre[val]]=suf[val];
        pre[suf[val]]=pre[val];
        pre[val]=0;
        suf[val]=0;
    }
}

inline void insertval(int val){
    suf[val]=head;
    pre[head]=val;
    head=val;
}

inline void add(int pos){
    cnt[val[pos]]++;
    int lst=cnt[val[pos]]-1;
    int now=cnt[val[pos]];
    sum[lst]-=sortv[val[pos]];
    sum[now]+=sortv[val[pos]];
    if(lst>0&&sum[lst]==0){
        deleteval(lst);
    }
    if(sum[cnt[val[pos]]]==sortv[val[pos]]){
        insertval(now);
    }
}

inline void del(int pos){
    cnt[val[pos]]--;
    int lst=cnt[val[pos]]+1;
    int now=cnt[val[pos]];
    sum[now]+=sortv[val[pos]];
    sum[lst]-=sortv[val[pos]];
    if(sum[lst]==0){
        deleteval(lst);
    }
    if(cnt[val[pos]]&&sum[cnt[val[pos]]]==sortv[val[pos]]){
        insertval(now);
    }
}

inline long long fun(int a,int b,int p){
    long long ans1=(bigpower[a/d]*smlpower[a%d])%p;
    long long ans2=(bigpower[b/d]*smlpower[b%d])%p;
    ans1=(ans1-ans2+p)%p;
    return ans1;
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=m;i++){
        int l=nums[i].l;
        int r=nums[i].r;
        int p=nums[i].p;
        int id=nums[i].id;
        int len=r-l+1;
        calc(p,len);

        while(winl>l){
            add(--winl);
        }
        while(winr<r){
            add(++winr);
        }
        while(winl<l){
            del(winl++);
        }
        while(winr>r){
            del(winr--);
        }

        long long res=0;
        for(int v=head;v;v=suf[v]){
            res+=(1ll*sum[v]*(fun(len,len-v,p)))%p;
        }
        res%=p;
        res=(res+p)%p;
        ans[id]=res;
    }
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

inline void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read(),nums[i].p=read();
        nums[i].id=i;
    }

    prepare();
    compute();

    for(int i=1;i<=m;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}