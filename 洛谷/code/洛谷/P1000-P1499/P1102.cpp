// https://www.luogu.com.cn/problem/P1102
// 题意：给 N 个数和差值 C。
// 统计有多少对下标对应的数 A、B 满足 A-B=C。位置不同的相同数分别计数。
// 数据范围：1 ≤ N ≤ 2 × 10^5，0 ≤ a[i] < 2^30，
// 1 ≤ C < 2^30。
// 算法标签：双指针、排序

#include<bits/stdc++.h>
using namespace std;

int n,c;
int nums[200005];

int main()
{
    cin>>n>>c;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    sort(nums+1,nums+n+1);
    int l=1,r=1;
    long long sum=0;
    for(int i=1;i<=n;i++){
        while(nums[l]<nums[i]-c&&l<n)
            l++;
        while(nums[r]<=nums[i]-c&&r<n)
            r++;
        if(nums[r]-nums[l]==c)
            sum+=r-l;
    }
    cout<<sum;
    return 0;
}
