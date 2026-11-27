// https://www.luogu.com.cn/problem/P10504
// 题意：有 N 项挑战，第 i 项成功概率为 p[i]%。
// 初始容量 K，成功时 a[i] 非负就增加该容量，
// a[i] 为 -1 就得到一个占一格的碎片。
// 求至少成功 L 项且最终能带走所有所得碎片的概率，保留六位小数。
// 数据范围：0 ≤ N ≤ 200，0 ≤ L ≤ N，0 ≤ K ≤ 2000，
// -1 ≤ a[i] ≤ 1000，0 ≤ p[i] ≤ 100。
// 算法标签：概率动态规划

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
