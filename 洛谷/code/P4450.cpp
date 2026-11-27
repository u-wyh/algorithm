// https://www.luogu.com.cn/problem/P4450
// 题意：给定 A, B, d，求满足 1 <= a <= A、1 <= b <= B 且 gcd(a, b) = d 的有序正整数对 (a, b) 的个数。
// 数据范围：1 <= A, B <= 10^6，1 <= d <= min(A, B)。
#include<bits/stdc++.h>
// 算法标签：容斥原理
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int f[MAXN];

signed main()
{
    int a,b,d;
    cin>>a>>b>>d;
    if(d>min(a,b)){
        cout<<0<<endl;
        return 0;
    }
    a=(a/d),b=(b/d);
    int k=min(a,b);
    for(int i=k;i>=1;i--){
        f[i]=(a/i)*(b/i);
        for(int j=2;j<=k/i;j++){
            f[i]-=f[j*i];
        }
    }
    cout<<f[1]<<endl;
    return 0;
}