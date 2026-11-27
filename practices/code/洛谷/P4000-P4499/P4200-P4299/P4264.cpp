// https://www.luogu.com.cn/problem/P4264
// 题意：数轴上有 N 堆牛粪，第 i 堆要从 a_i 运到 b_i；
// 可以在 x=0 建一个传送器终点在
// y（从 a_i 到 0 再瞬移到 y 最后到 b_i，
// 也可不用传送器直接从 a_i 到 b_i）
// 选择一个最优的 y 使总行驶距离最小。
// 数据范围：1 <= N <= 1e5，
// -1e8 <= a_i, b_i <= 1e8。
// 算法标签：组合数学
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 9999991;

signed main()
{
    int n;
    cin>>n;
    int ans=1;
    for(int i=1;i<n;i++){
        ans=(ans*i)%MOD;
    }
    for(int i=1;i<n-1;i++){
        ans=(ans*n)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}