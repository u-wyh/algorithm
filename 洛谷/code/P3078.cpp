// https://www.luogu.com.cn/problem/P3078
// 题意：输入牌面种类数 N，以及 1 到 N 号每种牌面当前的持有张数 a_i。
// 每次可以打出一个连续区间 [i, j] 的「顺子」（区间内每种牌面各消耗 1 张）。
// 求清空所有手牌最少需要打出多少次顺子。
// 输出一个整数表示最少顺子数。
// 数据范围：1 <= N <= 10^5，0 <= a_i <= 10^5。
#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005];
long long ans=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        ans+=max(nums[i]-nums[i-1],0);
    }
    cout<<ans;
    return 0;
}
