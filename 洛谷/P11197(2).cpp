#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n;
struct node{
    int a,b,c;
};
node nums[MAXN];
node tmp[MAXN];

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

bool cmp3(node a,node b){
    return a.c<b.c;
}

void merge(int l,int m,int r,int op){
    int p1,p2;
    for(p1=l-1,p2=m+1;p2<=r;p2++){
        while(p1+1<=m&&((op==1)?(nums[p1+1].b<=nums[p2].b):(op==2)?(nums[p1+1].c<=nums[p2].c):(nums[p1+1].a<=nums[p2].a))){
            p1++;
        }
        ans+=p1-l+1;
    }
    p1 = l;
    p2 = m + 1;
    int i = l;
    while (p1 <= m && p2 <= r) {
        if(op==1){
            tmp[i++] = nums[p1].b <= nums[p2].b ? nums[p1++] : nums[p2++];
        }
        else if(op==2){
            tmp[i++] = nums[p1].c <= nums[p2].c ? nums[p1++] : nums[p2++];
        }
        else{
            tmp[i++] = nums[p1].a <= nums[p2].a ? nums[p1++] : nums[p2++];
        }
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

void cdq(int l,int r,int op){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid,op);
    cdq(mid+1,r,op);
    merge(l,mid,r,op);
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        read();
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
    cdq(1,n,1);
    sort(nums+1,nums+n+1,cmp2);
    cdq(1,n,2);
    sort(nums+1,nums+n+1,cmp3);
    cdq(1,n,3);
    ans-=1ll*(n*(n-1))/2;
    ans/=2;
    cout<<ans<<endl;
    return 0;
}