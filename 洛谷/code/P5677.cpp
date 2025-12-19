#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXM = 3e5+5;

int n,m;
struct node{
    int num,id;
}arr[MAXN];
int tree[MAXN<<1];
int cnt=0;
struct con{
    int l,r;
}mix[MAXN<<1];
struct prob{
    int l,r,id,ans;
}nums[MAXM];

bool cmp1(node a,node b){
    return a.num<b.num;
}

bool cmp2(con a,con b){
    return a.r<b.r;
}

bool cmp3(prob a,prob b){
    return a.r==b.r?a.l<b.l:a.r<b.r;
}

inline void add(node a,node b){
    mix[++cnt].l=min(a.id,b.id);
    mix[cnt].r=max(a.id,b.id);
}

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
        //相当于把所有包含该状态的数字都增加
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
        //相当于将整个区间拆分开为几个小区间加速  和乘法快速幂相似
    }
    return ans;
}
//这个函数求的是从1到i所有数字的和

signed main()
{
    cin>>n>>m;
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        cin>>arr[i].num;
        arr[i].id=i;
    }
    sort(arr+1,arr+n+1,cmp1);
    add(arr[1],arr[2]);
    add(arr[n],arr[n-1]);
    for(int i=2;i<n;i++){
        if((arr[i].num-arr[i-1].num)==(arr[i+1].num-arr[i].num)){
            add(arr[i],arr[i-1]);
            add(arr[i],arr[i+1]);
        }
        if((arr[i].num-arr[i-1].num)>(arr[i+1].num-arr[i].num)){
            add(arr[i],arr[i+1]);
        }
        if((arr[i].num-arr[i-1].num)<(arr[i+1].num-arr[i].num)){
            add(arr[i],arr[i-1]);
        }
    }
    sort(mix+1,mix+cnt+1,cmp2);
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp3);
    int now=0;
    for(int i=1;i<=m;i++){
        while(mix[now].r<=nums[i].r&&now<=cnt){
            if(now!=0)
                add(mix[now].l,1);
            now++;
        }
        nums[i].ans=(now-1)-sum(nums[i].l-1);
    }
    long long ans=0;
    for(int i=1;i<=m;i++){
        ans+=(nums[i].id*nums[i].ans);
    }
    cout<<ans<<endl;
    return 0;
}
