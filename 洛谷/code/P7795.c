// https://www.luogu.com.cn/problem/P7795
// 题意：给定长为 n 的正整数序列 a，求长度至少为 k 的连续子序列的最大平均值（相对误差不超过 10^-3）。
// 数据范围：1 <= k <= n <= 3*10^5，1 <= a_i <= 10^6。
#include<stdio.h>
#include<stdbool.h>
#define MAX 300000+5


int n,k;
double nums[MAX];
double sum[MAX];

bool check(double x){
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+nums[i]-x;
	double minv=0,ret=0;
	for(int i=k,j=0;i<=n;i++,j++)
	{
		minv=minv<sum[j]?minv:sum[j];
		if(sum[i]-minv>=0)
            return 1;
	}
	return 0;
}

int main()
{
    scanf("%d %d",&n,&k);
    double l=0,r=0,mid,ans;
    for(int i=1;i<=n;i++){
        scanf("%lf",&nums[i]);
        r=r>nums[i]?r:nums[i];
    }
    while(r-l>1e-6){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid;
        }else{
            r=mid;
        }
    }
    printf("%.6lf",ans);
    return 0;
}
