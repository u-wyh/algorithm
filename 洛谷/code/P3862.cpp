// https://www.luogu.com.cn/problem/P3862
// 题意：第一行输入数据组数 T，接下来 T 行每行输入一个整数 n。
// 求 n 个顶点的无向完全图删去一条边后简单圈（顶点和边均不重复的闭合途径）的个数。
// 每组输出一行整数，答案模 998244353。
// 数据范围：1 <= T <= 10，3 <= n <= 10^9。
#include<bits/stdc++.h>
// 算法标签：递推、组合数学
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e5+5;

int a[MAXN];
int b[MAXN];

void prepare(int n){
    a[3]=1,b[3]=2;
    for(int i=4;i<=n;i++){
        b[i]=(b[i-1]*(i-2)+1)%MOD;
    }
    for(int i=4;i<=n;i++){
        a[i]=(a[i-1]+((i-2)*(i-1)/2)%MOD*b[i-1])%MOD;
    }
    // for(int i=1;i<=10;i++){
    //     cout<<i<<": "<<a[i]<<' '<<b[i]<<endl;
    // }
}

signed main()
{
    prepare(100000);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int ans=(a[n-1]+((n-2)*(n-3)/2)%MOD*b[n-1]%MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}