// https://www.luogu.com.cn/problem/P7399
// 题意：初始长为 n 的全 0 数组，
// 每次操作可将区间 [l, r] 加上正整数 x，
// 要求任意两次操作的区间要么不交要么包含；
// 求变为目标数组 a 的最少操作次数。
// 数据范围：1 <= n <= 10^5，0 <= a_i <= 10^9。
// 算法标签：单调栈
#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005],r=0,ans;
int st[100005];

int main()
{
    cin>>n;
    ans=n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            if(nums[st[r-1]]==nums[i]){
                ans--;
            }
            r--;
        }
        st[r++]=i;
    }
    //这道题做法的思想是一开始将答案设置为每一位置都单独进行增加
    //然后我们考虑优化
    //如果有两个等高的柱子  并且中间只有比自己高的  并且是先增后减  只有一个转折
    //那么可以减少一次
    //否则不能连续操作
    cout<<ans;
    return 0;
}
