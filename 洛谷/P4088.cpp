#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = MAXN*4;
const int INF = 1e9+1;

int n,q;
int x[MAXN],y[MAXN],t[MAXN];
int a[MAXN],b[MAXN];

struct node{
    int op,x,y,id;
};
node nums[MAXN*2];
node tmp[MAXN*2];

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

bool cmp(node a,node b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    if(a.y!=b.y){
        return a.y<b.y;
    }
    return a.op<b.op;
}

void merge(int l,int m,int r){
    int p1,p2;
    int minn=4e9;
    for(p1=l-1,p2=m+1;p2<=r;p2++){
        while(p1+1<=m&&nums[p1+1].y<=nums[p2].y){
            p1++;
            if(nums[p1].op==1){
                minn=min(minn,nums[p1].id-nums[p1].x-nums[p1].y);
            }
        }
        if(nums[p2].op==2){
            ans[nums[p2].id]=min(ans[nums[p2].id],nums[p2].x+nums[p2].y+minn);
        }
    }
    p1=l,p2=m+1;
    int i=l;
    while(p1<=m&&p2<=r){
        tmp[i++]=(nums[p1].y<=nums[p2].y)?nums[p1++]:nums[p2++];
    }
    while(p1<=m){
        tmp[i++]=nums[p1++];
    }
    while(p2<=r){
        tmp[i++]=nums[p2++];
    }
    for(int i=l;i<=r;i++){
        nums[i]=tmp[i];
    }
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

void to1(){
    for(int i=1;i<=n;i++){
        nums[i]={1,x[i],y[i],t[i]};
    }
    for(int i=1;i<=q;i++){
        nums[n+i]={2,a[i],b[i],i};
    }
    sort(nums+1,nums+n+q+1,cmp);
    cdq(1,n+q);
}

void to2(){
    for(int i=1;i<=n;i++){
        nums[i]={1,INF-x[i],y[i],t[i]};
    }
    for(int i=1;i<=q;i++){
        nums[n+i]={2,INF-a[i],b[i],i};
    }
    sort(nums+1,nums+n+q+1,cmp);
    cdq(1,n+q);
}

void to3(){
    for(int i=1;i<=n;i++){
        nums[i]={1,x[i],INF-y[i],t[i]};
    }
    for(int i=1;i<=q;i++){
        nums[n+i]={2,a[i],INF-b[i],i};
    }
    sort(nums+1,nums+n+q+1,cmp);
    cdq(1,n+q);
}

void to4(){
    for(int i=1;i<=n;i++){
        nums[i]={1,INF-x[i],INF-y[i],t[i]};
    }
    for(int i=1;i<=q;i++){
        nums[n+i]={2,INF-a[i],INF-b[i],i};
    }
    sort(nums+1,nums+n+q+1,cmp);
    cdq(1,n+q);
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        x[i]=read(),y[i]=read(),t[i]=read();
    }
    for(int i=1;i<=q;i++){
        a[i]=read(),b[i]=read();
    }
    for(int i=1;i<=q;i++){
        ans[i]=abs(a[i]-b[i]);
    }
    to1();
    to2();
    to3();
    to4();
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}