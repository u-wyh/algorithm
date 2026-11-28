// https://www.luogu.com.cn/problem/P6812
// 题意：若序列 a 对序列 b 在长度 min(|a|,|b|) 内逐位
// 满足 a_i <= b_i 则称 a 比 b 屑；
// 若序列比它的所有后缀都屑则称其为先辈。
// 维护长为 n 的序列支持 k 次操作：区间 [l, r] 加 x
// 以及查询区间 [l, r]
// 是否为先辈（数据中 r 可能取到 n+1，需自行令 r=n）。
// 数据范围：1 <= n, k <= 10^6，
// |a_i|, |x| <= 10^9。
// 难度评分：1600（洛谷分级换算）
// 算法标签：线段树、差分
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int arr[MAXN],Min[MAXN<<2],diff[MAXN];
int n,m;


void up(int i){
    Min[i]=min(Min[i<<1],Min[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        Min[i]=diff[l];
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobl,int jobv,int l,int r,int i){
    if(l==r){
        Min[i]+=jobv;
    }else{
        int mid=(l+r)/2;
        if(jobl<=mid){
            update(jobl,jobv,l,mid,i<<1);
        }else{
            update(jobl,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        return Min[i];
    }
    int mid = (l + r) >> 1;
    int ans = 1;
    if (jobl <= mid) {
        ans =min(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =min(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        diff[i]=arr[i]-arr[i-1];
    }
    build(1,n,1);
    for(int i=1,op,l,r,v;i<=m;i++){
        cin>>op>>l>>r;
        if(op==1){
            cin>>v;
            update(l,v,1,n,1);
            update(r+1,-v,1,n,1);
        }else{
            if(query(l,r,1,n,1)>0)
                cout<<"Yes\n";
            else
                cout<<"No\n";
        }
    }
    return 0;
}
