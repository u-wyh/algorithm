// https://www.luogu.com.cn/problem/P10416
// 题意：每次给一个区间 [L,R]，
// 统计有多少个有序三元组 (X,Y,Z) 满足 X+Y=Z，且三个数都在区间内。
// 交换 X 和 Y 后按不同三元组计数。
// 数据范围：1 ≤ T ≤ 10^5，1 ≤ L ≤ R ≤ 10^9。
// 算法标签：数学、等差数列求和

#include<bits/stdc++.h>
using namespace std;
#define int long long

int l,r;
unsigned long long ans=0;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>l>>r;
        if(r-l<l){
            cout<<0<<endl;
            continue;
        }
        ans=1ll*(r-2*l+2)*(r-2*l+1)/2;
        cout<<ans<<endl;
    }
    return 0;
}