// https://www.luogu.com.cn/problem/P5004
// 题意：有 N 个排成一行的格子，从 1 号格左边无限远跳到 N 号格右侧外，
// 每次从当前格子跳到目标格子中间必须至少空出 M 格（也可直接跳出终点）
// 求经过格子集合不同的合法方案数模 10^9 + 7。
// 数据范围：
// 1 <= N <= 10^18，
// M <= 15（测试点中 M 为 1, 2, 3, 5, 10, 15）。
// 算法标签：矩阵快速幂、动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

int n,m;

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int p=0;p<k;p++){
                ans[i][j]+=a[i][p]*b[p][j];
                ans[i][j]%=MOD;
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>> a,int p){
    int n=a.size();
    vector<vector<int>>base(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        base[i][i]=1;
    }
    while(p){
        if(p&1){
            base=multiply(base,a);
        }
        p>>=1;
        a=multiply(a,a);
    }
    return base;
}

signed main()
{
    cin>>n>>m;
    if(n<m+1){
        cout<<2<<endl;
        return 0;
    }
    vector<vector<int>>base(m+1,vector<int>(m+1,0));
    vector<vector<int>>nums(1,vector<int>(m+1,1));
    for(int i=0;i<=m;i++){
        nums[0][i]=m-i+1;
    }
    base[0][0]=base[m][0]=1;
    for(int i=0;i<m;i++){
        base[i][i+1]=1;
    }
    // for(int i=0;i<=m;i++){
    //     for(int j=0;j<=m;j++){
    //         cout<<base[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    nums=multiply(nums,power(base,n-m));
    cout<<nums[0][0]<<endl;
    return 0;
}