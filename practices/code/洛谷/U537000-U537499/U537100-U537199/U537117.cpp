// https://www.luogu.com.cn/problem/U537117
// 题意：每组给一个正整数 n。
// 求 i 从 1 到 n 的 floor(n / i) 之和。
// 输入：第一行 T，接着 T 行，每行一个 n。
// 输出：每组输出一个整数。
// 数据范围：1 <= n <= 10^9，T 为正整数。
// 难度评分：1400（估算）
// 算法标签：整除分块
#include<bits/stdc++.h>
using namespace std;
#define int long long

int solve(int n){
    int ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;
        ans+=v*(rt-lt+1);
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
        cout<<solve(n)<<endl;
    }
    return 0;
}