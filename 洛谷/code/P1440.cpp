// https://www.luogu.com.cn/problem/P1440
// 题意：给一个长为 n 的序列。对每个位置 i，取它前面至多 m 个元素，求其中的最小值。
// 窗口到左端时只取实际存在的元素，不包含 a[i]。第一个位置前面没有数，输出 0。
// 数据范围：1 ≤ m ≤ n ≤ 2 × 10^6，1 ≤ a[i] ≤ 3 × 10^7。

#include<bits/stdc++.h>
using namespace std;

int n,k;
int minh=0,mint=0;
int minq[10000005];
int nums[10000005];

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=0;i<n;i++){
        if(i==0)
            cout<<'0'<<endl;
        else
            cout<<nums[minq[minh]]<<endl;
        while(minh<mint&&i-minq[minh]>=k){
            minh++;
        }
        while(minh<mint&&nums[i]<=nums[minq[mint-1]]){
            mint--;
        }
        minq[mint++]=i;
    }
    return 0;
}

