#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

int n;

struct node{
    int x,y1,y2,d;
};
node nums[MAXN<<1];

int point[MAXN][4];

int m=1;
int arr[MAXN<<1];

int tree[MAXN<<2];
int sum[MAXN<<2];
int cnt[MAXN<<2];

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

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
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

bool cmp(node a,node b){
    if(a.x!=b.x) 
        return a.x<b.x;
    return a.d>b.d;
}

void up(int i){
    if(cnt[i]){
        sum[i]=tree[i];
    }
    else{
        sum[i]=sum[i<<1]+sum[i<<1|1];
    }
}

void build(int l,int r,int i){
    tree[i]=arr[r+1]-arr[l];
    sum[i]=0,cnt[i]=0;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        cnt[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
    up(i);
}

long long scan(){
    long long ans=0;
    int pre=0;
    for(int i=1;i<=2*n;i++){
        pre=sum[1];
        add(nums[i].y1,nums[i].y2,nums[i].d,1,m-1,1);
        ans+=abs(pre-sum[1]);
    }
    return ans;
}

long long scany(){
    for(int i=1;i<=n;i++){
        arr[i*2-1]=point[i][1],arr[i*2]=point[i][3];
    }
    sort(arr+1,arr+2*n+1);
    m=1;
    for(int i=2;i<=2*n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        int l=find(point[i][1]);
        int r=find(point[i][3])-1;
        nums[i*2-1]={point[i][0],l,r,1};
        nums[i*2]={point[i][2],l,r,-1};
    }
    sort(nums+1,nums+2*n+1,cmp);
    build(1,m-1,1);
    long long ans=scan();
    return ans;
}

long long scanx(){
    for(int i=1;i<=n;i++){
        arr[i*2-1]=point[i][0],arr[i*2]=point[i][2];
    }
    sort(arr+1,arr+2*n+1);
    m=1;
    for(int i=2;i<=2*n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        int l=find(point[i][0]);
        int r=find(point[i][2])-1;
        nums[i*2-1]={point[i][1],l,r,1};
        nums[i*2]={point[i][3],l,r,-1};
    }
    sort(nums+1,nums+2*n+1,cmp);
    build(1,m-1,1);
    long long ans=scan();
    return ans;
}

long long compute(){
    long long a=scany();
    long long b=scanx();
    // cout<<a<<' '<<b<<endl;
    return (a+b);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        point[i][0]=read(),point[i][1]=read(),point[i][2]=read(),point[i][3]=read();
    }
    cout<<compute();
    return 0;
}