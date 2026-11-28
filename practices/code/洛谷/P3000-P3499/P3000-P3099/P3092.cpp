// https://www.luogu.com.cn/problem/P3092
// 题意：输入硬币数 K、物品数 N，K 个硬币各自的面值，
// 以及按顺序要买的 N 个物品价格 c_i。
// 购买过程中可用 1
// 个硬币一次性买下从上次付款后到当前为止的连续一段物品（面值需 >= 区间总价），
// 且不找零。
// 求按顺序买完所有 N 个物品后，钱包里最多能剩下多少钱；无法买完输出 -1。
// 输出一个整数表示最大剩余金额或 -1。
// 数据范围：1 <= K <= 16，硬币面值在 [1, 10^8] 内，
// 1 <= N <= 10^5，1 <= c_i <= 10^4。
// 难度评分：2000（洛谷分级换算）
// 算法标签：状态压缩动态规划、二分查找、前缀和
#include<bits/stdc++.h>
using namespace std;

int n,m;
int coin[17],shop[100005];
int sum[100005];
int dp[1<<17],f[1<<17];
int ans=INT_MAX;

int check(int left, int limit) {
	int l = left, r = m, mid;
	int ans=left;
	while(l<=r){
        mid=(l+r)/2;
        if(sum[mid]-sum[left]<=limit){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    int tot=0;
    for(int i=1;i<=n;i++){
        cin>>coin[i];
        tot+=coin[i];
    }
    //cout<<' '<<tot<<endl;;
    for(int i=1;i<=m;i++){
        cin>>shop[i];
        sum[i]=sum[i-1]+shop[i];
    }
//    for(int i=1;i<=m;i++){
//        cout<<sum[i]<<' ';
//    }
//    cout<<endl;
//    sum[0]=shop[0];
//    for(int i=1;i<m;i++){
//        sum[i]=sum[i-1]+shop[i];
//    }
    for(int i=2;i<(1<<(n+1));i++){
        for(int j=1;j<=n;j++){
            if(i&(1<<j)){
                int sum=check(dp[i^(1<<j)],coin[j]);
                if(sum>dp[i]){
                    dp[i]=sum;
                    f[i]=f[i^(1<<j)]+coin[j];
                    if(dp[i]==m){
                        ans=min(ans,f[i]);
                    }
                }
            }
        }
        //cout<<i<<' '<<dp[i]<<' '<<f[i]<<endl;
    }
    //cout<<endl;
    if(tot-ans<0)
        ans=-1;
    else
        ans=tot-ans;
    cout<<ans;
    return 0;
}
