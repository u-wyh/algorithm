#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;

int a[MAXN];
int b[MAXN];

int posa[MAXN];
int posb[MAXN];

struct node{
    int a,b,id;
};

node nums[MAXN];

int tree[MAXN];

long long ans=0;

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

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
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

bool cmpa(node a,node b){
    return a.a<b.a;
}

bool cmpb(node a,node b){
    return a.b<b.b;
}

void merge(int l,int mid,int r){
    int winl=l;
    for(int i=l;i<=mid;i++){
        add(nums[i].id,1);
    }
    for(int p2=mid+1;p2<=r;p2++){
        while(winl<=mid&&nums[winl].b<nums[p2].b){
            add(nums[winl].id,-1);
            winl++;
        }
        ans-=(query(min(n,nums[p2].id+k))-query(max(1,nums[p2].id-k)-1));
    }
    for(int i=winl;i<=mid;i++){
        add(nums[i].id,-1);
    }
    sort(nums+l,nums+r+1,cmpb);
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

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        posa[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
        posb[b[i]]=i;
    }
    for(int i=n;i>=1;i--){
        ans+=query(posb[a[i]]-1);
        add(posb[a[i]],1);
    }
    // cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        tree[i]=0;
    }
    for(int i=1;i<=n;i++){
        nums[i].a=posa[i];
        nums[i].b=posb[i];
        nums[i].id=i;
    }
    sort(nums+1,nums+n+1,cmpa);
    cdq(1,n);
    cout<<ans<<endl;
    return 0;
}