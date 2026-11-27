// https://www.luogu.com.cn/problem/P7716
// 题意：T 组数据，n x m 棋盘，
// 从编号 1..k 的 1x2 纸片中选 [l, r] 张按编号从小到大横放
// 或竖放（后放覆盖先放）；
// 给定最终棋盘各格最上层编号，求满足条件的不同放置方案数对 10^9+7 取模。
// 数据范围：1 <= T <= 10，2 <= n, m, k <= 10^3，
// 1 <= l <= r <= k。
// 算法标签：计数统计、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m,k,l,r;
int nums[1005][1005];
int cnt[1005],big[1005],ans[1005];

int main()
{
    int test;
    cin>>test;
    while(test--){
        for(int i=1;i<=1000;i++){
            cnt[i]=0;
            big[i]=0;
            ans[i]=0;
        }
        cin>>n>>m>>k>>l>>r;
        k=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>nums[i][j];
                k=max(k,nums[i][j]);
                cnt[nums[i][j]]++;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(i+1<=n){
                    if(nums[i+1][j]>nums[i][j]){
                        big[nums[i][j]]++;
                    }
                    if(nums[i+1][j]<nums[i][j]){
                        big[nums[i+1][j]]++;
                    }
                }
                if(j+1<=m){
                    if(nums[i][j+1]>nums[i][j]){
                        big[nums[i][j]]++;
                    }
                    if(nums[i][j+1]<nums[i][j]){
                        big[nums[i][j+1]]++;
                    }
                }
            }
        }
        int count=0;
        int temp=0;
        long result=1;
        for(int i=k;i>=1;i--){
            if(cnt[i]==2){
                ans[i]=1;
            }
            else if(cnt[i]==1){
                ans[i]+=big[i];
            }
            else{
                if(cnt[i+1]==0){
                    ans[i]=temp;
                }
                else{
                    ans[i]=temp+1+big[i+1];
                }
            }
            if(cnt[i]){
                count++;
                result=(result*ans[i])%MOD;
            }
        }
        int low=l-count,high=r-count;

    }
    return 0;
}
