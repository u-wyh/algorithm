// https://www.luogu.com.cn/problem/P9691
// 题意：多组数据（共 T 组）。
// 数轴位置 1..n 建基站的成本分别为 a_1..a_n。
// 有 m 条需求，
// 第 i 条要求区间 [l_i, r_i] 内至少建有 1 座基站。
// 求满足所有需求的最小总成本。
// 题意：第一行输入 T，
// 每组输入 n、a_1..a_n、m 及 m 行 (l_i, r_i)；
// 每组输出一行一个整数。
// 数据范围：1 <= n, m <= 5 * 10^5，
// 1 <= a_i <= 10^9，1 <= l_i <= r_i <= n
// sum(n),
// sum(m) <= 5 * 10^5
// （未显式给出 T 上界，受 sum(n), sum(m) 限制）。
// 难度评分：1600（洛谷分级换算）
// 算法标签：动态规划、单调队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
long long arr[MAXN];
int q[MAXN];
long long f[MAXN];
int pre[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        arr[++n]=0;
        for(int i=1;i<=n;i++){
            f[i]=pre[i]=0;
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int l,r;
            cin>>l>>r;
            pre[r+1]=max(pre[r+1],l);
        }
        for(int i=1;i<=n;i++){
            pre[i]=max(pre[i],pre[i-1]);
        }
        int l=1,r=0;
        q[++r]=0;
        for(int i=1;i<=n;++i){
            while(l<=r&&q[l]<pre[i]) ++l;
            f[i]=f[q[l]]+arr[i];
            while(l<=r&&f[q[r]]>=f[i]) --r;
            q[++r]=i;
        }
        cout<<f[n]<<endl;
    }
    return 0;
}
