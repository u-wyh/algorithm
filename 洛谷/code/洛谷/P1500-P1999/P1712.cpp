// https://www.luogu.com.cn/problem/P1712
// 题意：从 n 个闭区间里选 m 个，要求它们至少共享一个点。
// 区间长度为 r_i−l_i，求所选最长区间与最短区间的长度差最小是多少。
// 无解输出 -1。
// 数据范围：1 ≤ n ≤ 5×10^5，
// 1 ≤ m ≤ min(n,2×10^5)，
// 0 ≤ l_i ≤ r_i ≤ 10^9。
// 算法标签：线段树、双指针、离散化

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int x[MAXN<<1];
int cnt=0;
struct node{
    int l,r,len;
}nums[MAXN];
int n,m;
int tot;
int tree[MAXN*8];
int lazy[MAXN*8];

bool cmp(node a,node b){
    return a.len<b.len;
}

int getrank(int val){
    int l=1,r=tot,ans=tot;
    while(l<=r){
        int mid=(l+r)/2;
        if(x[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        return;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int v){
    tree[i]+=v;
    lazy[i]+=v;
}

void down(int i){
    if(lazy[i]){
        downlazy(i<<1,lazy[i]);
        downlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        downlazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//汇总修改数据
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        return tree[i];
    } else {
        int ans=0;
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            ans=max(ans,query(jobl, jobr,l, mid, i << 1));
        }
        if (jobr > mid) {
            ans=max(ans,query(jobl, jobr,mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
        x[++cnt]=nums[i].l;
        x[++cnt]=nums[i].r;
        nums[i].len=nums[i].r-nums[i].l;
    }
    sort(x+1,x+cnt+1);
    for(int i=1;i<=cnt;i++){
        if(x[i]!=x[i-1]){
            x[++tot]=x[i];
        }
    }
    build(1,tot,1);
    for(int i=1;i<=n;i++){
        nums[i].l=getrank(nums[i].l);
        nums[i].r=getrank(nums[i].r);
    }
    sort(nums+1,nums+n+1,cmp);
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].l<<' '<<nums[i].r<<' '<<nums[i].len<<endl;
//    }
    int ans=INT_MAX;
    add(nums[1].l,nums[1].r,1,1,tot,1);
    for(int l=1,r=1;l<=n&&r<=n;l++){
        while(tree[1]<m&&r<n){
            r++;
            add(nums[r].l,nums[r].r,1,1,tot,1);
        }
        if(tree[1]>=m){
            ans=min(ans,nums[r].len-nums[l].len);
            add(nums[l].l,nums[l].r,-1,1,tot,1);
        }
    }
    if(ans==INT_MAX){
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}
