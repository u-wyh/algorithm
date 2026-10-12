// 用途：单点加值、区间求和；输入 n m 与 m 次操作。
// 时间：建树 O(n log n)，单次操作 O(log n)。
// 空间：O(n)。
// 注意：下标从 1 开始；和值用 long long。
// 例题：https://www.luogu.com.cn/problem/P3374
// 题意：数组单点加值并多次求区间和。
// 思路：树状数组维护前缀和，区间和由两个前缀相减。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

long long tree[MAXN];
int n,m;

// lowbit 给出当前树状数组节点覆盖区间的长度。
int lowbit(int x){
    return x & -x;
}

void add(int i,long long v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}

long long sum(int i){
    long long ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}

long long query(int l,int r){
    return sum(r)-sum(l-1);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        long long v;
        cin>>v;
        add(i,v);
    }
    for(int i=1,op;i<=m;i++){
        cin>>op;
        if(op==1){
            int x;
            long long v;
            cin>>x>>v;
            add(x,v);
        }else {
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}
