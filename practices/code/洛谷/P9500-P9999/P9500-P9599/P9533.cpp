// https://www.luogu.com.cn/problem/P9533
// 题意：给定长度为 n 的非负整数数组 a。
// 若区间 [l, r] 异或和为 0 则称其为“灵异区间”。
// 可任意次选择一个当前为灵异区间的 [l, r] 并将其内部元素翻转。
// 求最终数组中最多能有多少个灵异区间。
// 题意：第一行输入 n，第二行输入 a_1..a_n；输出一行一个整数。
// 数据范围：1 <= n <= 10^5，0 <= a_i < 2^20。
// 难度评分：1200（洛谷分级换算）
// 算法标签：前缀异或、计数统计
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];
int cnt[1<<20];

int main()
{
    cin>>n;
    long long ans=0;
    cnt[0]=1;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]^=nums[i-1];
        //printf("%3d",nums[i]);
        ans+=cnt[nums[i]]++;
    }
    cout<<ans;
    return 0;
}

