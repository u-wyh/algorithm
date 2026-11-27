// https://www.luogu.com.cn/problem/P4863
// 题意：给定正整数 A 和 B，求 sum_{i=A}^B sum_{j=1}^i floor(i / j) * (-1)^j 的值。
// 数据范围：1 <= A <= B <= 2 * 10^7。
#include<bits/stdc++.h>
// 算法标签：数学、前缀和
using namespace std;
#define int long long

int a,d;
int ans1,ans2;

signed main()
{
    cin>>a>>d;
    a--;
    int flag=-1;
    for(int i=1;i<=a;i++){
        int b=(a-i+1)/i;
        int c=(a-i+1)%i;
        ans1+=flag*(i*(b+1)*b/2+c*(b+1));
        flag*=-1;
    }
    flag=-1;
    for(int i=1;i<=d;i++){
        int b=(d-i+1)/i;
        int c=(d-i+1)%i;
        // cout<<i<<": "<<flag*(i*(b+1)*b/2+c*(b+1))<<endl;
        ans2+=flag*(i*(b+1)*b/2+c*(b+1));
        flag*=-1;
    }
    // cout<<ans1<<' '<<ans2<<endl;
    cout<<(ans2-ans1)<<endl;
    return 0;
}