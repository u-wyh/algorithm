// https://www.luogu.com.cn/problem/P3743
// 题意：输入设备数 n 和充电器每秒充能量 p，以及每个设备每秒耗能量 a_i 与初始能量 b_i。
// 所有设备同时匀速耗能，充电器任一时刻可连续给任一设备以速率 p 充能（切换耗时忽略），直到某个设备能量降为 0 为止。
// 若可无限使用输出 -1，否则输出最多可使用的时间（绝对或相对误差不超过 10^-4）。
// 数据范围：1 <= n <= 10^5，1 <= p <= 10^5，1 <= a_i, b_i <= 10^5。
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool check(double ans,double m,int n,double *a ,double *b){
    double p=ans*m;
    double sum=0;
    for(int i=1;i<=n;i++){
		if(a[i]*ans<=b[i]){//若设备已有的能量大于使用时间需要的能量
			continue;//忽略该设备
		}
		sum+=(a[i]*ans-b[i]);//否则用充电器充电，使设备已有的能量等于使用时间需要的能量，并记录需要的能量。
	}
	return sum<=p;
}

int main()
{
    int n;
    double m,sum=0;
    scanf("%d %lf",&n,&m);
    double a[n+1],b[n+1];
    double ans,l=0,r=1e6,mid;
    for(int i=1;i<=n;i++){
        scanf("%lf %lf",&a[i],&b[i]);
        sum+=a[i];
    }
    if(m>=sum){
        printf("-1\n");
        return 0;
    }
    while(r-l>1e-8){
        mid=(l+r)/2;
        if(check(mid,m,n,a,b)){
            l=mid;
        } else{
            r=mid;
        }
    }
    printf("%lf",l);
    return 0;
}
