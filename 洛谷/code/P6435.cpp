// https://www.luogu.com.cn/problem/P6435
// 题意：
// 给定一行五个非负整数 n, a, b, c, p。
// 初始数列为 1, 2, ..., n；每轮将相邻两项替换为 a * 左 + b * 右 + c。
// 重复操作直到数列只剩一项。
// 输出最终唯一项对 p 取模的结果。
// 数据范围：
// 1 <= n <= 10^{18}
// 1 <= p <= 10^{14}（80% 数据 p 为质数）
// 1 <= a, b <= 10^9
// 0 <= c <= 10^9
// 算法标签：矩阵快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a,b,c;
int mod;

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>> ans(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int p=0;p<k;p++){
                ans[i][j]+=a[i][p]*b[p][j];
                ans[i][j]%=mod;
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
    cin>>n>>a>>b>>c>>mod;
    vector<vector<int>>nums(1,vector<int>(3,1));
    vector<vector<int>>base(3,vector<int>(3,0));
    base[0][0]=a+b;
    base[1][0]=b,base[1][1]=a+b;
    base[2][0]=c,base[2][2]=1;
    nums=multiply(nums,power(base,n-1));
    //cout<<nums[0][0]<<' '<<nums[0][1]<<' '<<nums[0][2]<<endl;
    cout<<nums[0][0]<<endl;
    return 0;
}