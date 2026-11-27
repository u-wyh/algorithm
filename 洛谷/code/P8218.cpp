// https://www.luogu.com.cn/problem/P8218
// 题意：给定长为 n 的正整数序列 a_1..a_n 和 m 个区间 [l_i, r_i]，依次输出每个区间的元素和。
// 数据范围：100% 数据满足 1 <= n, m <= 10^5，1 <= a_i <= 10^4，1 <= l_i <= r_i <= n。
// 算法标签：前缀和
#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[100005];
long long sum[100005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
    }
    int i,j;
    cin>>m;
    while(m--){
        cin>>i>>j;
        cout<<sum[j]-sum[i-1]<<endl;
    }
    return 0;
}
