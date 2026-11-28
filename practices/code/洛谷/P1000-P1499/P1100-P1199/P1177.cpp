// https://www.luogu.com.cn/problem/P1177
// 题意：读入 n 个整数 a[i]，按从小到大的顺序输出，数字之间用空格隔开。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ a[i] ≤ 10^9。
// 难度评分：900（洛谷分级换算）
// 算法标签：排序

#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    sort(nums+1,nums+n+1);
    for(int i=1;i<=n;i++)
        printf("%d ",nums[i]);
    return 0;
}
