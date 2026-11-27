// https://www.luogu.com.cn/problem/P4329
// 题意：有 N 个人和 N 项任务，给出每人完成每项任务的成功百分比概率，求一一配对完成所有任务的最大成功总概率（各任务概率乘积，以百分比输出
// 误差 <= 1e-6）。
// 数据范围：1 <= N <= 20，输入百分比为 0 到 100 的整数。
#include<bits/stdc++.h>
// 算法标签：状态压缩动态规划
using namespace std;

int n;
double a[20][20];
double dp[(1<<20)];

int main()
{
    //cout<<(2&(1<<1))<<endl;
    cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%lf",&a[i][j]);
			a[i][j]*=0.01;
		}
	}
	dp[0]=1;
	for(int i=1;i<(1<<n);i++){
        int cnt=0;
        for(int x=i;x;x>>=1){
            if(x&1){
                cnt++;//统计1个数
            }
        }
        cnt--;
        //cout<<i<<' '<<cnt<<' ';
        for(int j=0;j<n;j++){
            //cout<<666<<' ';
            if((i&(1<<j))){
                //cout<<j<<' ';
                dp[i]=max(dp[i],dp[i^(1<<j)]*a[cnt][j]);
            }
        }
        //cout<<dp[i]<<endl;
	}
	printf("%.6lf",dp[(1<<n)-1]*100);
    return 0;
}
