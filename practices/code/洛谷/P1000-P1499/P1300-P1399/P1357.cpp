// https://www.luogu.com.cn/problem/P1357
// 题意：把环上的 n 个有编号位置各设为 C 或 P，首尾相邻。
// 要求每一段环上连续 m 个位置内，C 的个数都不超过 k。
// 求合法安排数，对 10^9+7 取模。
// 数据范围：2 ≤ n ≤ 10^15，2 ≤ m ≤ min(n,5)，
// 1 ≤ k<m。
// 难度评分：2000（洛谷分级换算）
// 算法标签：状态压缩动态规划、矩阵快速幂

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

int n,m,k;
int cnt[32];

vector<vector<int>> multiply(vector<vector<int>>a,vector<vector<int>>b){
    int n=a.size();
    int m=b[0].size();
    int k=a[0].size();
    vector<vector<int>>ans(n,vector<int>(m,0));
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

vector<vector<int>> power(vector<vector<int>>a,int b){
    int n=a.size();
    vector<vector<int>> m(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        m[i][i]=1;
    }
    while(b){
        if(b&1){
            m=multiply(m,a);
        }
        b>>=1;
        a=multiply(a,a);
    }
    return m;
}

signed main()
{
    cnt[0]=0;
    for(int i=1;i<32;i++){
        cnt[i]=cnt[i-(i&-i)]+1;
    }
    cin>>n>>m>>k;
    int tot=(1<<m);
    vector<vector<int>>nums(tot,vector<int>(tot,0));
    for(int i=0,j;i<tot;i++){
        if(cnt[i]>k){
            continue;
        }
        j=i>>1;
        nums[j][i]=1;
        j = (i >> 1) | (1 << (m - 1));
		if (cnt[j] <= k){
			nums[j][i] = 1;
		}
    }
    nums=power(nums,n);
    int ans=0;
    for(int i=0;i<tot;i++){
        ans+=nums[i][i];
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}
