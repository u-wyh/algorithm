#include<bits/stdc++.h>
using namespace std;
const int MAXN = 152505;
const int MAXM = 52505;

int n,m,z,q;
int a[MAXN];
int b[MAXM];

int blen;
int bi[MAXM];

struct node{
    int l,r,id;
};
node nums[MAXM];
int ans[MAXM];

int match[MAXN<<2];
int resta[MAXN<<2];
int overb[MAXN<<2];

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

void up(int i){
    int l=i<<1;
    int r=i<<1|1;
    int newmatch=min(resta[l],overb[r]);
    resta[i]=resta[l]+resta[r]-newmatch;
    overb[i]=overb[l]+overb[r]-newmatch;
    match[i]=match[l]+match[r]+newmatch;
}

void build(int l,int r,int i){
    if(l==r){
        resta[i]=1;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void prepare(){
    sort(a+1,a+n+1);
    blen=sqrt(m);
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(nums+1,nums+q+1,cmp);
    build(1,n,1);
}

void add(int jobv,int l,int r,int i){
    if(l==r){
        if(resta[i]==1){
            match[i]=1;
            resta[i]=0;
        }
        else{
            overb[i]++;
        }
    }
    else{
        int mid=(l+r)>>1;
        if(jobv+a[mid+1]<=z){
            add(jobv,mid+1,r,i<<1|1);
        }
        else if(jobv+a[l]<=z){
            add(jobv,l,mid,i<<1);
        }
        up(i);
    }
}

void del(int jobv,int l,int r,int i){
    if(l==r){
        if(overb[i]){
            overb[i]--;
        }
        else{
            match[i]=0;
            resta[i]=1;
        }
    }
    else{
        int mid=(l+r)>>1;
        if(jobv+a[mid+1]<=z){
            del(jobv,mid+1,r,i<<1|1);
        }
        else if(jobv+a[l]<=z){
            del(jobv,l,mid,i<<1);
        }
        up(i);
    }
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=q;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobi=nums[i].id;
        while(winl>jobl){
            add(b[--winl],1,n,1);
        }
        while(winr<jobr){
            add(b[++winr],1,n,1);
        }
        while(winl<jobl){
            del(b[winl++],1,n,1);
        }
        while(winr>jobr){
            del(b[winr--],1,n,1);
        }
        ans[jobi]=match[1];
    }
}

// void compute(){
//     int winl=1,winr=0;
//     for(int i=1;i<=q;i++){
//         int jobl=nums[i].l;
//         int jobr=nums[i].r;
//         int jobi=nums[i].id;
//         while(winl>jobl){
//             add(b[--winl],1,n,1);
//         }
//         while(winl<jobl){
//             del(b[winl++],1,n,1);
//         }
//         while(winr<jobr){
//             add(b[++winr],1,n,1);
//         }
//         while(winr>jobr){
//             del(b[winr--],1,n,1);
//         }
//         ans[jobi]=match[1];
//     }
// }

int main()
{
    n=read(),m=read(),z=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=m;i++){
        b[i]=read();
    }
    q=read();
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