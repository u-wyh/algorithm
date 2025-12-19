#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;

int dp[MAXN];

int m=1;
int arr[MAXN*3];

struct node{
    int d,p,q,a,id;
};

int tree[MAXN*3];

node nums[MAXN];
node tmp[MAXN];

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
    return a.d<b.d;
}

bool cmpa(node a,node b){
    return a.a<b.a;
}

bool cmpq(node a,node b){
    return a.q<b.q;
}

bool cmpp(node a,node b){
    return a.p<b.p;
}

int find(int val){
    int l=1,r=m,ans;
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

inline int lowbit(int x){
    return x&-x;
}

void update(int x,int val){
    while(x<=m){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void clear(int x){
    while(x<=m){
        tree[x]=0;
        x+=lowbit(x);
    }
}

void merge(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        tmp[i]=nums[i];
    }
    sort(tmp+l,tmp+mid+1,cmpa);
    sort(tmp+mid+1,tmp+r+1,cmpp);
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&tmp[p1+1].a<=tmp[p2].p){
            p1++;
            update(tmp[p1].q,dp[tmp[p1].id]);
        }
        dp[tmp[p2].id]=max(dp[tmp[p2].id],query(tmp[p2].a)+1);
    }
    for(int i=l;i<=p1;i++){
        clear(tmp[i].q);
    }
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)/2;
    cdq(l,mid);
    merge(l,mid,r);
    cdq(mid+1,r);
}

void prepare(){
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        nums[i].id=i;
    }
    for(int i=1;i<=n;i++){
        arr[1+3*(i-1)]=nums[i].p;
        arr[2+3*(i-1)]=nums[i].q;
        arr[3*i]=nums[i].a;
    }
    sort(arr+1,arr+3*n+1);
    for(int i=2;i<=3*n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].p=find(nums[i].p);
        nums[i].q=find(nums[i].q);
        nums[i].a=find(nums[i].a);
    }
    for(int i=1;i<=n;i++){
        dp[i]=1;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].d=read(),nums[i].p=read(),nums[i].q=read(),nums[i].a=read();
    }
    prepare();
    cdq(1,n);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}