#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 505;

int n,m;
int val[MAXN];
struct node{
    int l,r,id;
};
node nums[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];

int cnt[MAXN];
int mex;
int ans[MAXN];

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
    return a.r>b.r;
}

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
    }
    sort(nums+1,nums+m+1,cmp);
}

void del(int val){
    cnt[val]--;
    if(cnt[val]==0){
        mex=min(mex,val);
    }
}

void add(int val){
    cnt[val]++;
}

void compute(){
    for(int i=1;i<=n;i++){
        cnt[val[i]]++;
    }
    mex=0;
    while(cnt[mex]){
        mex++;
    }
    int winl=1,winr=n;
    for(int b=1,qi=1;qi<=m&&b<=bnum;b++){
        while(winl<bl[b]){
            del(val[winl++]);
        }
        int beforejob=mex;
        for(;qi<=m&&bi[nums[qi].l]==b;qi++){
            int jobl=nums[qi].l;
            int jobr=nums[qi].r;
            int jobi=nums[qi].id;
            while(winr>jobr){
                del(val[winr--]);
            }
            int backup=mex;
            while(jobl>winl){
                del(val[winl++]);
            }
            ans[jobi]=mex;

            mex=backup;
            while(winl>bl[b]){
                add(val[--winl]);
            }
        }
        while(winr<n){
            add(val[++winr]);
        }
        mex=beforejob;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    prepare();
    compute();
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}