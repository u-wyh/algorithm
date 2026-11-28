// https://www.luogu.com.cn/problem/P6433
// 题意：有 n 道题（毒瘤度 a_i、出数据耗时 x_i），剩余时间 m；
// 有 k 个老师可将至多 k 道不同题的毒瘤度翻倍，
// 且父母会拿走 1 道题（老师和父母行动均可控制且必须执行）。
// 求最终能完成的题目的最大毒瘤度之和。
// 数据范围：0 <= a_i <= 1000，0 <= x_i <= m，
// 0 <= m <= 1000，0 <= n <= 100，k < n。
// 难度评分：1500（洛谷分级换算）
// 算法标签：背包动态规划、贪心
#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int dp[1005][105];
int a[105],x[105];

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cin>>n>>m>>k;
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>x[i];
        sum+=x[i];
    }
    if (sum<=m)	{
		int ans=0;
		sort(a+1,a+1+n,cmp);
		for (int i=1;i<=k;i++)
			ans+=a[i]*2;
		for (int i=k+1;i<n;i++)
			ans+=a[i];
		cout<<ans;
		return 0;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
        for(int j=m;j>=x[i];j--){
            for(int l=min(k,i);l>=1;l--){
                dp[j][l]=max(dp[j][l],max(dp[j-x[i]][l]+a[i],dp[j-x[i]][l-1]+2*a[i]));
                ans=max(ans,dp[j][l]);
            }
            dp[j][0]=max(dp[j][0],dp[i-x[i]][0]+a[i]);
            ans=max(ans,dp[j][0]);
        }
	}
	cout<<ans<<endl;
    return 0;
}
