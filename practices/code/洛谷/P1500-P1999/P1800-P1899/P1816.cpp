// https://www.luogu.com.cn/problem/P1816
// 题意：给定 m 笔账的金额和 n 次询问。
// 每次给出账目编号 a、b，求闭区间 [a,b] 内的最小金额。
// 所有答案用空格隔开。
// 数据范围：1 ≤ m,n ≤ 10^5，0 ≤ x_i ≤ 10^5，
// 1 ≤ a ≤ b ≤ m。
// 难度评分：1400（洛谷分级换算）
// 算法标签：ST表、倍增

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 350005;
const int LIMIT = 17;

int n,m;
int st[MAXN][LIMIT];
int Log2[MAXN],arr[MAXN];

void build(int n){
    Log2[0]=-1;
    for(int i=1;i<=n;i++){
        Log2[i]=Log2[i>>1]+1;
        st[i][0]=arr[i];
    }
    for(int p=1;p<=Log2[n];p++){
        for(int i=1;i<=n;i++){
            st[i][p]=min(st[i][p-1],st[i+(1<<(p-1))][p-1]);
        }
    }
}

int query(int l,int r){
    int p=Log2[r-l+1];
    return min(st[l][p],st[r-(1<<p)+1][p]);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(n);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<' ';
    }
    return 0;
}
