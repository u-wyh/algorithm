// https://www.luogu.com.cn/problem/P3275
// 题意：给 N 个小朋友分糖果，每人至少分到 1 颗，需满足 K 条不等关系。
// X=1: A=B；X=2: A<B；X=3: A>=B；X=4: A>B；
// X=5: A<=B。
// 输出最少需要的总糖果数；若无解输出 -1。
// 数据范围：
// 1 <= N, K <= 10^5（人数与条件数）
// 1 <= X <= 5（关系类型）
// 1 <= A, B <= N（小朋友编号）
// 算法标签：差分约束、迭代松弛
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct candy{
	int X,A,B;
}q[101010];
int n,k;
int a[101010];
int main()
{
	cin>>n>>k;
	for (int i=1; i<=k; i++){
		scanf("%d%d%d",&q[i].X,&q[i].A,&q[i].B);
	}
	for (int i=1; i<=n; i++) a[i]=1;
	for (int T=1; T<=200; T++){
		for (int i=1; i<=k; i++){
			if (q[i].X==1) {
				if (a[q[i].A]>a[q[i].B]) a[q[i].B]=a[q[i].A];
				else a[q[i].A]=a[q[i].B];
			}
			else if (q[i].X==2){
				if (a[q[i].A]>=a[q[i].B]) a[q[i].B]=a[q[i].A]+1;
			}
			else if (q[i].X==3){
				if (a[q[i].A]<a[q[i].B]) a[q[i].A]=a[q[i].B];
			}
			else if (q[i].X==4){
				if (a[q[i].A]<=a[q[i].B]) a[q[i].A]=a[q[i].B]+1;
			}
			else if (q[i].X==5){
				if (a[q[i].A]>a[q[i].B]) a[q[i].B]=a[q[i].A];
			}
		}
	}
	for (int i=1; i<=k; i++){
		if (q[i].X==1) {
				if (a[q[i].A]>a[q[i].B]) {cout<<"-1";return 0;}
			}
			else if (q[i].X==2){
				if (a[q[i].A]>=a[q[i].B]) {cout<<"-1";return 0;}
			}
			else if (q[i].X==3){
				if (a[q[i].A]<a[q[i].B]) {cout<<"-1";return 0;}
			}
			else if (q[i].X==4){
				if (a[q[i].A]<=a[q[i].B]) {cout<<"-1";return 0;}
			}
			else if (q[i].X==5){
				if (a[q[i].A]>a[q[i].B]) {cout<<"-1";return 0;}
			}
	}
	long long ans=0;
	for (int i=1; i<=n; i++) ans+=a[i];
	cout<<ans<<endl;
	return 0;
}
