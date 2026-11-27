// https://codeforces.com/problemset/problem/1045/G
// 题意：n 个机器人各有位置 x_i、视野 r_i 与智商 q_i。
// 规则：若 |x_i-x_j| <= min(r_i,r_j)
// 且 |q_i-q_j| <= K 则可交流。
// 输出：可相互交流的无序机器人对数。
// 数据范围：1 <= n <= 10^5。
// 0 <= K <= 20，
// 0 <= x_i, r_i, q_i <= 10^9。
// 算法标签：CDQ分治、树状数组、离散化
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;

struct node{
    int x,y,q;
    int l,r;
}nums[MAXN];

int m=1;
int arr[MAXN];

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

bool cmpy(node a,node b){
    return a.y>b.y;
}

bool cmpq(node a,node b){
    return a.q<b.q;
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

long long merge(int l,int mid,int r){
    int winl=l,winr=l-1;
    long long ans=0;
    for(int i=mid+1;i<=r;i++){
        while(winl<=mid&&nums[winl].q<nums[i].q-k){
            add(nums[winl].x,-1);
            winl++;
        }
        while(winr+1<=mid&&nums[winr+1].q<=nums[i].q+k){
            winr++;
            add(nums[winr].x,1);
        }
        ans+=(query(nums[i].r)-query(nums[i].l-1));
    }
    for(int i=winl;i<=winr;i++){
        add(nums[i].x,-1);
    }
    sort(nums+l,nums+r+1,cmpq);
    return ans;
}

long long cdq(int l,int r){
    if(l==r){
        return 0;
    }
    int mid=(l+r)>>1;
    return cdq(l,mid)+cdq(mid+1,r)+merge(l,mid,r);
}

//找到第一个大于val的位置
int find1(int val){
    int l=1,r=m,ans=1+m;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

//找到第一个大于等于val的位置
int find2(int val){
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

void prepare(){
    sort(arr+1,arr+n+1);
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].l=find2(nums[i].x-nums[i].y);
        nums[i].r=find1(nums[i].x+nums[i].y)-1;
        nums[i].x=find2(nums[i].x);
    }
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i].x=read();
        arr[i]=nums[i].x;
        nums[i].y=read();
        nums[i].q=read();
    }
    prepare();
    sort(nums+1,nums+n+1,cmpy);
    printf("%lld\n",cdq(1,n));
    return 0;
}