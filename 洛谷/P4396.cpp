#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m;
int val[MAXN];

int blen;
int bi[MAXN];

int vlen,vnum;
int vi[MAXN];
int vl[MAXB];
int vr[MAXB];

int blocknum[MAXB];
int blocksum[MAXB];
int cnt[MAXN];

struct node{
    int l,r,a,b,id;
};
node nums[MAXN];
int ans1[MAXN];
int ans2[MAXN];

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
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }

    vlen=sqrt(MAXN-1);
    vnum=(MAXN-1+vlen-1)/vlen;
    for(int i=1;i<MAXN;i++){
        vi[i]=(i-1)/vlen+1;
    }
    for(int i=1;i<=vnum;i++){
        vl[i]=(i-1)*vlen+1;
        vr[i]=min(MAXN-1,i*vlen);
    }
    sort(nums+1,nums+m+1,cmp);
}

void add(int val){
    cnt[val]++;
    blocksum[vi[val]]++;
    if(cnt[val]==1){
        blocknum[vi[val]]++;
    }
}

void del(int val){
    cnt[val]--;
    blocksum[vi[val]]--;
    if(cnt[val]==0){
        blocknum[vi[val]]--;
    }
}

pair<int,int>query(int l,int r){
    int lv=vi[l],rv=vi[r];
    int res1=0,res2=0;
    if(lv==rv){
        for(int i=l;i<=r;i++){
            if(cnt[i]){
                res1+=cnt[i];
                res2++;
            }
        }
    }
    else{
        for(int i=l;i<=vr[lv];i++){
            if(cnt[i]){
                res1+=cnt[i];
                res2++;
            }
        }
        for(int i=lv+1;i<rv;i++){
            res1+=blocksum[i];
            res2+=blocknum[i];
        }
        for(int i=vl[rv];i<=r;i++){
            if(cnt[i]){
                res1+=cnt[i];
                res2++;
            }
        }
    }
    return {res1,res2};
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
        pair<int,int>tmp=query(joba,jobb);
        ans1[jobi]=tmp.first;
        ans2[jobi]=tmp.second;
    }
    for(int i=1;i<=m;i++){
        printf("%d %d\n",ans1[i],ans2[i]);
    }
    return 0;
}