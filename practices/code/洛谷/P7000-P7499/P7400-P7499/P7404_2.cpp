// https://www.luogu.com.cn/problem/P7404
// 题意：给定长为 N 的序列 A，每次可将区间 [L, R] 所有数加 1
// 求使新序列 B 成为单峰序列
// （存在 k 使 B_1 < ... < B_k
// 且 B_k > ... > B_N）的最少操作次数。
// 数据范围：1 <= N <= 2*10^5，1 <= A_i <= 10^9。
// 难度评分：1200（洛谷分级换算）
// 算法标签：差分、前缀和、贪心
#include<bits/stdc++.h>
using namespace std;
const int N=200010;

int a[N],b[N];
long long x[N],y[N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i]-a[i-1];
    }
    for(int i=2,j=n;i<=n;i++,j--){
        x[i]=(b[i]<=0?x[i-1]-(b[i]-1):x[i-1]);
        y[j]=(b[j]>=0?y[j+1]+(b[j]+1):y[j+1]);
    }
    long long ans=LONG_LONG_MAX;
    for(int i=1;i<=n;i++)
        ans=min(ans,max(x[i],y[i+1]));
    cout<<ans;
    return 0;
}
