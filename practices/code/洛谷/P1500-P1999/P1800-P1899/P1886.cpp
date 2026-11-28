// https://www.luogu.com.cn/problem/P1886
// 题意：给一个长为 n 的序列和一个宽度为 k 的窗口。
// 从最左边的 k 个数开始，每次把窗口往右移一格，直到右边界到达序列末尾。
// 第一行按顺序输出每个窗口的最小值，第二行输出最大值。
// 数据范围：1 ≤ k ≤ n ≤ 10^6，
// -2^31 ≤ a[i] < 2^31。
// 难度评分：1400（洛谷分级换算）
// 算法标签：单调队列、滑动窗口

#include<bits/stdc++.h>
using namespace std;

int n,k;
int minh=0,mint=0,maxh=0,maxt=0;
int minq[1000005],maxq[1000005];
int nums[1000005];

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=0;i<n;i++){
        while(minh<mint&&i-minq[minh]>=k){
            minh++;
        }
        while(minh<mint&&nums[i]<=nums[minq[mint-1]]){
            mint--;
        }
        minq[mint++]=i;
        if(i>=k-1)
            cout<<nums[minq[minh]]<<' ';
    }
    printf("\n");
    for(int i=0;i<n;i++){
        while(maxh<maxt&&i-maxq[maxh]>=k){
            maxh++;
        }
        while(maxh<maxt&&nums[i]>=nums[maxq[maxt-1]]){
            maxt--;
        }
        maxq[maxt++]=i;
        if(i>=k-1)
            cout<<nums[maxq[maxh]]<<' ';
    }
    printf("\n");
    return 0;
}
