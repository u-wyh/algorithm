#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,q;
int val[MAXN];
int cnt1[MAXN];
int cnt2[MAXN];

int head;
int nxt[MAXN];
int pre[MAXN];

struct Query {
    int l, r, id;
};
Query nums[MAXN];
int ans[MAXN];

int blen;
int bi[MAXN];

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

bool cmp(Query &a, Query &b) {
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
    sort(nums+1,nums+q+1,cmp);
    cnt2[0]=n+1;
}

void removenode(int val){
    if(pre[val]!=0){
        nxt[pre[val]]=nxt[val];
    }
    else{
        head=nxt[val];
    }
    if(nxt[val]){
        pre[nxt[val]]=pre[val];
    }
}

void addnode(int val){
    nxt[val]=head;
    if(head){
        pre[head]=val;
    }
    pre[val]=0;
    head=val;
}

void add(int val){
    int old=cnt1[val];
    cnt2[old]--;
    if(cnt2[old]==0){
        removenode(old);
    }
    cnt1[val]++;
    cnt2[cnt1[val]]++;
    if(cnt2[cnt1[val]]==1){
        addnode(cnt1[val]);
    }
}

void del(int val){
    int old=cnt1[val];
    cnt2[old]--;
    if(cnt2[old]==0){
        removenode(old);
    }
    cnt1[val]--;
    cnt2[cnt1[val]]++;
    if(cnt2[cnt1[val]]==1){
        addnode(cnt1[val]);
    }
}

int query(){
    int ans=0;
    for(int i=head;i;i=nxt[i]){
        ans=max(ans,cnt2[i]*i);
    }
    return ans;
}

void compute(){
    int winl = 1, winr = 0;
    for (int i = 1; i <= q; i++) {
        int jobl = nums[i].l;
        int jobr = nums[i].r;
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
        ans[nums[i].id] = query();
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
        printf("%d\n",ans[i]);
    }
    return 0;
}