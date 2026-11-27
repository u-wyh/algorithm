// https://www.luogu.com.cn/problem/P5337
// 题意：给定正整数 n 和小写字母字符串 s1，
// 求长为 n 的小写字母字符串 s2 的个数。
// 要求 s1 中任意相邻两个字母不能以相同顺序在 s2 中相邻出现，
// 答案对 10^9+7 取模。
// 数据范围：1 <= n <= 10^15，|s1| <= 10^5。
// 算法标签：矩阵快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXM = 100005;

int n,m;
char s[MAXM];

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
    cin>>n;
    scanf("%s",s);
    m=strlen(s);
    vector<vector<int>>nums(26,vector<int>(26,1));
    for(int i=0;i<m-1;i++){
        int u=s[i]-'a';
        int v=s[i+1]-'a';
        nums[u][v]=0;
    }
    int ans=0;
    nums=power(nums,n-1);
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            ans+=nums[i][j];
        }
    }
    ans%=MOD;
    cout<<ans<<endl;
    return 0;
}