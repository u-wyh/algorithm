#include<bits/stdc++.h>
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
