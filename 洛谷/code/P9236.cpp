// https://www.luogu.com.cn/problem/P9236
// 题意：给定长度为 n 的数组 A_1..A_n，求所有满足 1 <= L <= R <= n 的子段 [L, R] 的区间异或和之和。
// 题意：第一行输入 n，第二行输入 A_1..A_n；输出一行一个整数。
// 数据范围：1 <= n <= 10^5，0 <= A_i <= 2^20。
// 算法标签：位运算、前缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin>>n;
    int arr[n+1];
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    long long ans=0;
    for(int i=0;i<=20;i++){
        int s=0,n0=0,n1=0;
        for(int j=1;j<=n;j++){
            s+=(arr[j]>>i)&1;
            if(s%2==1){
                ans+=(1+n0)*(1<<i);
                n1++;
            }
            else{
                ans+=(n1)*(1<<i);
                n0++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
