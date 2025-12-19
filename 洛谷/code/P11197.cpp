#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
struct node{
    int a,b,c;
};
node nums[MAXN];
node tmp[MAXN];

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

bool cmp1(node a,node b){
    return a.a<b.a;
}

bool cmp2(node a,node b){
    return a.b<b.b;
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

inline int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void merge(int l,int m,int r){
    int p1,p2;
    for(p1=l-1,p2=m+1;p2<=r;p2++){
        while(p1+1<=m&&nums[p1+1].b<nums[p2].b){
            p1++;
            add(nums[p1].c,1);
        }
        ans+=query(nums[p2].c);
    }
    for(int i=l;i<=p1;i++){
        add(nums[i].c,-1);
    }
    p1 = l;
    p2 = m + 1;
    int i = l;
    while (p1 <= m && p2 <= r) {
        tmp[i++] = nums[p1].b <= nums[p2].b ? nums[p1++] : nums[p2++];
    }
    while (p1 <= m) {
        tmp[i++] = nums[p1++];
    }
    while (p2 <= r) {
        tmp[i++] = nums[p2++];
    }
    for (i = l; i <= r; i++) {
        nums[i] = tmp[i];
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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int val=read();
    }
    for(int i=1;i<=n;i++){
        int val=read();
        nums[val].a=i;
    }
    for(int i=1;i<=n;i++){
        int val=read();
        nums[val].b=i;
    }
    for(int i=1;i<=n;i++){
        int val=read();
        nums[val].c=i;
    }
    sort(nums+1,nums+n+1,cmp1);
    cdq(1,n);
    cout<<ans<<endl;
    return 0;
}