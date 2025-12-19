#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;
const int MAXB = 405;

int n,m;
int val[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int blockcnt[MAXB];
int numcnt[MAXN];

struct node{
    int l,r,a,b,id;
};
node nums[MAXM];
int ans[MAXM];

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
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    sort(nums+1,nums+m+1,cmp);
}

void add(int val){
    numcnt[val]++;
    if(numcnt[val]==1){
        blockcnt[bi[val]]++;
    }
}

void del(int val){
    numcnt[val]--;
    if(numcnt[val]==0){
        blockcnt[bi[val]]--;
    }
}

int query(int l,int r){
    int lb=bi[l],rb=bi[r];
    int res=0;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            if(numcnt[i]){
                res++;
            }
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            if(numcnt[i]){
                res++;
            }
        }
        for(int i=lb+1;i<rb;i++){
            res+=blockcnt[i];
        }
        for(int i=bl[rb];i<=r;i++){
            if(numcnt[i]){
                res++;
            }
        }
    }
    return res;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read(),nums[i].a=read(),nums[i].b=read();
        nums[i].id=i;
    }
    prepare();
    int winl=1,winr=0;
    for(int i=1;i<=m;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobi=nums[i].id;
        int joba=nums[i].a;
        int jobb=nums[i].b;
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
        ans[jobi]=query(joba,jobb);
    }
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}