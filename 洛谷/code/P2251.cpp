// https://www.luogu.com.cn/problem/P2251
// 题意：给定长度为 N 的序列 A，求所有长度为 M 的连续子段的最小值。
// 共输出 N-M+1 行，每行一个最小值。
// 数据范围：1 <= M <= N <= 10^5，A_i <= 10^6。
#include<bits/stdc++.h>
// 算法标签：单调队列、滑动窗口
using namespace std;

int n,k;
int minh=0,mint=0;
int minq[1000005];
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
            cout<<nums[minq[minh]]<<endl;
    }
    return 0;
}

