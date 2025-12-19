#include<bits/stdc++.h>
using namespace std;
const int N=205;
int n,l,kk,a[N];
double p[N];
double f[N][N][N*2];
int main(){
	cin>>n>>l>>kk;
   /*由于最多只有 n 次挑战，也就是最多只有 n 块地图*/
   /*所以 kk 和 a 数组都可以对 n 取 min*/
	kk=min(kk,n);
	for(int i=1;i<=n;i++){
		cin>>p[i];
		p[i]/=100;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=min(a[i],n);
	}
	f[0][0][kk+200]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=400;k++){
				f[i][j][k]=f[i-1][j][k]*(1-p[i]);
				if(j!=0)f[i][j][k]+=f[i-1][j-1][max(k-a[i],0)]*p[i];
			}
		}
	}
	double ans=0;
	for(int i=l;i<=n;i++){
		for(int k=200;k<=400;k++){
			ans+=f[n][i][k];
		}
	}
	printf("%.6lf",ans);
	return 0;
}
