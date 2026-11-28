// https://www.luogu.com.cn/problem/P1102
// 题意：给 N 个数和差值 C。
// 统计有多少对下标对应的数 A、B 满足 A-B=C。位置不同的相同数分别计数。
// 数据范围：1 ≤ N ≤ 2 × 10^5，0 ≤ a[i] < 2^30，
// 1 ≤ C < 2^30。
// 难度评分：900（洛谷分级换算）
// 算法标签：二分查找、排序

#include<bits/stdc++.h>
using namespace std;
long a[200001];
long N,C,ans;
int main()
{
    cin>>N>>C;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+N+1);
    for(int i=1;i<=N;i++)
    {
        ans+=((upper_bound(a+1,a+N+1,a[i]+C)-a)-(lower_bound(a+1,a+N+1,a[i]+C)-a));
    }
    cout<<ans;
    return 0;
}
