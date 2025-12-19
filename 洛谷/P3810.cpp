#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXK = 2e5+5;

int n,k;

struct node{
    int sub,a,b,c;
}nums[MAXN];

int tree[MAXK];

int f[MAXN];
int ans[MAXN];

bool cmp1(node a,node b){
    if(a.a!=b.a){
        return a.a<b.a;
    }
    if(a.b!=b.b){
        return a.b<b.b;
    }
    return a.c<b.c;
}

bool cmp2(node a,node b){
    return a.b<b.b;
}

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int val){
    while(x<=k){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void prepare(){
    sort(nums+1,nums+n+1,cmp1);
    for(int l=1,r=1;l<=n;l=++r){
        while(r+1<=n&&nums[l].a==nums[r+1].a&&nums[l].b==nums[r+1].b&&nums[l].c==nums[r+1].c){
            r++;
        }
        for(int i=l;i<=r;i++){
            f[nums[i].sub]+=r-i;
        }
    }
}

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].b<=nums[p2].b){
            p1++;
            add(nums[p1].c,1);
        }
        f[nums[p2].sub]+=query(nums[p2].c);
    }
    for(int i=l;i<=p1;i++){
        add(nums[i].c,-1);
    }
    sort(nums+l,nums+r+1,cmp2);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)/2;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i].sub=i;
        nums[i].a=read();
        nums[i].b=read();
        nums[i].c=read();
    }
    prepare();
    cdq(1,n);
    for(int i=1;i<=n;i++){
        ans[f[i]]++;
    }
    for(int i=0;i<n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}