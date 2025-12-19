#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+1;
const int OFFSET = 1e5;
const int MAXB = 405;

int n,m,blen;
int val[MAXN];
int bi[MAXN];

struct node{
    int l,r,x,op,id;
};
node nums[MAXN];
int cntq;

int headq[MAXN];
int nxtq[MAXN];
int ql[MAXN];
int qr[MAXN];
int qid[MAXN];
int cntg=1;

int cnt[MAXN];
bitset<MAXN>bs1;
bitset<MAXN>bs2;

int pre[MAXN];
int dp[MAXN];

bool ans[MAXN];

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

void addspecial(int x,int l,int r,int id){
    nxtq[cntg]=headq[x];
    ql[cntg]=l;
    qr[cntg]=r;
    qid[cntg]=id;
    headq[x]=cntg++;
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

void add(int x){
    cnt[x]++;
    if(cnt[x]==1){
        bs1[x]=1;
        bs2[OFFSET-x]=1;
    }
}

void del(int x){
    cnt[x]--;
    if(cnt[x]==0){
        bs1[x]=0;
        bs2[OFFSET-x]=0;
    }
}

bool calc(int op,int x){
    if(op==1){
        return (bs1&(bs1>>x)).any();
    }
    else if(op==2){
        return (bs1&(bs2>>(OFFSET-x))).any();
    }
    else if(op==3){
        for(int f=1;f*f<=x;f++){
            if(x%f==0&&bs1[f]&&bs1[x/f]){
                return true;
            }
        }
        return false;
    }
    else{
        for(int i=1;i*x<=OFFSET;i++){
            if(bs1[i]&&bs1[i*x]){
                return true;
            }
        }
        return false;
    }
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=cntq;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobx=nums[i].x;
        int jobo=nums[i].op;
        int jobi=nums[i].id;
        while(winl>jobl){
            add(val[--winl]);
        }
        while(winr<jobr){
            add(val[++winr]);
        }
        while(winl<jobl){
            del(val[winl++]);
        }
        while(winr>jobr){
            del(val[winr--]);
        }
        ans[jobi]=calc(jobo,jobx);
    }
}

void special() {
    for (int x = 1; x < blen; x++) {
        if (headq[x] != 0) {
            memset(pre, 0, sizeof(int) * (OFFSET + 1));
            memset(dp, 0, sizeof(int) * (n + 1));
            for (int i = 1; i <= n; i++) {
                int v = val[i];
                pre[v] = i;
                dp[i] = dp[i-1];
                if (v * x <= OFFSET) {
                    dp[i] = max(dp[i], pre[v * x]);
                }
                if (v % x == 0) {
                    dp[i] = max(dp[i], pre[v / x]);
                }
            }
            for (int q = headq[x]; q > 0; q = nxtq[q]) {
                int l = ql[q];
                int r = qr[q];
                int id = qid[q];
                ans[id] = (l <= dp[r]);
            }
        }
    }
}

int main()
{
    n=read(),m=read();
    blen=sqrt(OFFSET);
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        int op,l,r,x;
        op=read(),l=read(),r=read(),x=read();
        if(op==4&&x<blen){
            addspecial(x,l,r,i);
        }
        else{
            nums[++cntq]={l,r,x,op,i};  
        }
    }
    sort(nums+1,nums+cntq+1,cmp);
    compute();
    special();
    for(int i=1;i<=m;i++){
        cout<<(ans[i]?"yuno":"yumi")<<endl;
    }
    return 0;
}