#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m;
int val[MAXN];

struct node{
    int l,r,p,id;
};
node nums[MAXN];
long long ans[MAXN];

int head;
int lst[MAXN];
int nxt[MAXN];

int blen;
int bi[MAXN];

int cnt[MAXN];
long long sum[MAXN];

long long smlpower[MAXB];
long long bigpower[MAXB];

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

void addnode(int x){
    lst[head]=x;
    nxt[x]=head;
    head=x;
}

void delnode(int x){
    if(x==head){
        head=nxt[head];
        lst[head]=0;
        nxt[x]=0;
    }
    else{
        nxt[lst[x]]=nxt[x];
        lst[nxt[x]]=lst[x];
        lst[x]=0;
        nxt[x]=0;
    }
}

void add(int val){
    if(cnt[val]>0){
        sum[cnt[val]]-=val;
    }
    if(cnt[val]>0&&sum[cnt[val]]==0){
        delnode(cnt[val]);
    }

    cnt[val]++;
    if(sum[cnt[val]]==0){
        addnode(cnt[val]);
    }
    sum[cnt[val]]+=val;
}

void del(int val){
    if(cnt[val]>0){
        sum[cnt[val]]-=val;
    }
    if(cnt[val]>0&&sum[cnt[val]]==0){
        delnode(cnt[val]);
    }

    cnt[val]--;
    if(cnt[val]>0&&sum[cnt[val]]==0){
        addnode(cnt[val]);
    }
    if(cnt[val]>0){
        sum[cnt[val]]+=val;
    }
}

void setans(int len,int p,int id){
    int blocklen=sqrt(len);
    int blocknum=(len+blocklen-1)/blocklen;
    smlpower[0]=1;
    for(int i=1;i<=blocklen;i++){
        smlpower[i]=(smlpower[i-1]<<1)%p;
    }
    bigpower[0]=1;
    for(int i=1;i<=blocknum;i++){
        bigpower[i]=(bigpower[i-1]*smlpower[blocklen])%p;
    }
    long long res=0,p1,p2,tmp;
    p1=bigpower[len/blocklen]*smlpower[len%blocklen]%p;
    for(int t=head;t;t=nxt[t]){
        p2=bigpower[(len-t)/blocklen]*smlpower[(len-t)%blocklen]%p;
        tmp=(p1-p2)*sum[t]%p;
        res=((res+tmp)%p+p)%p;
    }
    ans[id]=res;
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=m;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobp=nums[i].p;
        int jobi=nums[i].id;
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
        setans(jobr - jobl + 1, jobp, jobi);
    }
}

void prepare(){
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(nums+1,nums+m+1,cmp);
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
        printf("%lld\n",ans[i]);
    }
    return 0;
}