// https://www.luogu.com.cn/problem/P3166
// 题意：输入两个正整数 M 和 N，
// 表示一个 N*M 的网格（共有 (N+1)*(M+1) 个格点）。
// 从所有格点中任选三个不共线的点组成三角形。
// 输出能构成的格点三角形总数量。
// 数据范围：1 <= N, M <= 1000。
// 难度评分：1500（洛谷分级换算）
// 算法标签：组合数学、最大公约数
#include<bits/stdc++.h>
using namespace std;
#define int long long

int C3(int x){
    return x*(x-1)*(x-2)/6;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

signed main()
{
    int m,n;
    cin>>m>>n;

    // 实际格点数是 (n+1)*(m+1)
    int ans=C3((n+1)*(m+1));

    // 横着三点共线
    ans-=(n+1)*C3(m+1);

    // 竖着三点共线
    ans-=(m+1)*C3(n+1);

    // 斜着三点共线
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            // 坐标差为(i,j)的端点对数量
            // 两种斜率，所以乘2
            //
            // 两端点之间有 gcd(i,j)-1 个格点
            // 每个内部格点都可以作为第三个点
            ans-=2*(n+1-i)*(m+1-j)*(gcd(i,j)-1);
        }
    }

    cout<<ans<<endl;

    return 0;
}