// https://www.luogu.com.cn/problem/P1403
// 题意：给 N，求 1 到 N 的每个整数的正约数个数之和。
// 数据范围：1 ≤ N ≤ 10^6。
// 算法标签：数论分块

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;

    long long ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;

        ans+=1ll*v*(rt-lt+1);
    }
    cout<<ans<<endl;
    return 0;
}