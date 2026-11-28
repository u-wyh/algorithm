// https://onlinejudge.org/external/115/11526.pdf
// 题意：给 T 组数据，每组一个整数 n。
// 将 i 从 1 到 n 的各项整数商 n / i 加起来。
// 若 n <= 0，则没有任何项，和为 0。
// 输出：每组输出一行这个和。
// 数据范围：T <= 1000，n 为有符号 32 位整数。
// 难度评分：1400（估算）
// 算法标签：整除分块
#include<bits/stdc++.h>
using namespace std;
#define int long long

int compute(int n){
    if(n<=0){
        return 0;
    }
    int l=1,r;
    int ans=0;
    while(l<=n){
        int k=n/l;
        r=n/k;
        ans+=k*(r-l+1);
        l=r+1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<compute(n)<<endl;
    }
    return 0;
}