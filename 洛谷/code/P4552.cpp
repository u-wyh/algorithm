// https://www.luogu.com.cn/problem/P4552
// 题意：给定长度为 n 的数列，每次可选一个区间整体加 1 或整体减 1，求使所有数相等的最少操作次数，以及在最少次数下最终可能得到的数列种数。
// 数据范围：n <= 100000，0 <= a_i <= 2^{31}。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int nums[100005];
int d[100005];

signed main()
{
    cin>>n;
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        d[i]=nums[i]-nums[i-1];
        if(d[i]>0&&i!=1){
            ans1+=d[i];
        }
        if(d[i]<0&&i!=1){
            ans2-=d[i];
        }
    }
    int ans=0;
    cout<<max(ans1,ans2)<<endl;
    ans=abs(ans1-ans2)+1;
    cout<<ans<<endl;
    return 0;
}
