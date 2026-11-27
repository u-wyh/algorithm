// https://www.luogu.com.cn/problem/P4105
// 题意：输入 7 个正整数 n, S_a, S_b, S_c, S_d, A_1,
// Mod
// 按 F(x) = S_a*x^3 + S_b*x^2 + S_c*x + S_d
// 与 A_i = (F(A_{i-1}) + F(A_{i-2}))
// mod Mod（A_0 = 0）生成正整数数列 A_1..A_n。
// 构造一个不降正整数数列 B_1..B_n（B_i <= B_{i+1}），
// 最小化 max_{1<=j<=n} |A_j - B_j|。
// 输出一行一个正整数 Ans。
// 数据范围：
// 2 < n <= 5*10^6，S_a, S_b, S_c, S_d,
// A_1 <= min{10^4, Mod}
// 1 < Mod <= 10^9 + 7，输入均为正整数。
// 算法标签：贪心、模拟
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,a,b,c,d,mod;
int a1,a2,a3;

int f(int x){
    int ans=((((a*x%mod*x%mod*x%mod+b*x%mod*x%mod)%mod+c*x%mod)%mod+d)%mod+mod)%mod;
    return ans;
}

signed main()
{
    cin>>n>>a>>b>>c>>d>>a2>>mod;
    a1=0;
    int maxx=a2;
    int ans=0;
    n--;
    while(n--){
        a3=((f(a1)+f(a2))%mod+mod)%mod;
        if(maxx>a3){
            ans=max(ans,maxx-a3);
        }
        else{
            maxx=a3;
        }
        a1=a2;
        a2=a3;
    }
    cout<<(ans+1)/2<<endl;
    return 0;
}