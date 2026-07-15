#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,k;
struct node{
    int x,y;
}nums[MAXN];
int arr[MAXN];
int m;
int tree[MAXN];

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
    return a.x==b.x?a.y>b.y:a.x<b.x;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
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

void add(int x,int v){
    while(x<=m){
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

bool check(int limit){
    for(int i=1;i<=n;i++){
        arr[i]=nums[i].y-limit*nums[i].x;
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    // cout<<m<<endl;
    for(int i=1;i<=m;i++){
        tree[i]=0;
    }
    int all=0;
    for(int i=1;i<=n;i++){
        int d=nums[i].y-limit*nums[i].x;
        d=find(d);
        // cout<<i<<' '<<d<<endl;
        all+=query(d);
        add(d,1);
    }
    return all>=k;
}

signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i].x=read();
        nums[i].y=read();
    }
    sort(nums+1,nums+n+1,cmp);
    int l=-200000000,r=200000000,ans=0;
    while(l<=r){
        // cout<<l<<' '<<r<<endl;
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}