// https://www.luogu.com.cn/problem/P3225
// 题意：多组数据（以 0 结束），
// 每组输入隧道数 N 以及 N 条无向边 (S, T)（构成连通无向图）。
// 需要在若干节点设置救援出口，使得无论图中哪一个节点坍塌，
// 其余所有节点都能至少到达一个救援出口。
// 每组数据输出一行 "Case i: ans cnt"，
// 分别为最少救援出口数及最少出口数的设置方案总数。
// 数据范围：N <= 500，
// 节点最大编号 m 满足 1 <= m <= 10^3，答案小于 2^64。
// 难度评分：1900（洛谷分级换算）
// 算法标签：矩阵快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,mod,k,r;

vector<vector<int>> multiply(vector<vector<int>> a,const vector<vector<int>> b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]=((ans[i][j]%mod)+mod)%mod;
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>> m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

signed main()
{
    cin>>n>>mod>>k>>r;
    vector<vector<int>>base(k,vector<int>(k,0));
    for(int i=0;i<k;i++){
        base[i][i]=1;
        base[(i-1+k)%k][i]++;
    }
    vector<vector<int>>init(1,vector<int>(k,0));
    init[0][0]=1;
    vector<vector<int>>ans=multiply(init,power(base,n*k));
    cout<<ans[0][r]<<endl;
    return 0;
}