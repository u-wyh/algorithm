// https://www.luogu.com.cn/problem/P9641
// 题意：多组数据（共 T 组）。
// 给定 n * m 网格，每格有方向字符（u/d/l/r）和步长 a_{i,j}。
// 任选起点并标记，之后不断按当前格方向移动 a_{i,j} 步到达新格并标记；
// 若目标格越界或已标记则结束。
// 判断是否存在起点能恰好标记全部 n * m 个格子各一次。
// 题意：第一行输入 T，
// 每组输入 n, m、n 行方向字符矩阵、n 行整数矩阵 a_{i,j}；
// 输出 Yes 或 No。
// 数据范围：1 <= n * m <= 10^5，
// 1 <= a_{i,j} <= max(n, m)
// sum(n * m) <= 10^6
// （未显式给出 T 上界，受 sum(n * m) 限制）。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集、计数统计
#include<bits/stdc++.h>
using namespace std;
int n,m;
string str[100005];
int fa[100005],d[100005];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y,int x_,int y_){
	int s1=(x-1)*m+y,s2=(x_-1)*m+y_;
	int u=find(s1),v=find(s2);
	if(u!=v) fa[v]=u;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++){
		fa[i]=i;
		d[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>str[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			scanf("%d",&x);
			int ch=(int)str[i][j-1],p,q;
			if(ch==117) p=i-x,q=j;
			else if(ch==100) p=i+x,q=j;
			else if(ch==108) p=i,q=j-x;
			else p=i,q=j+x;
			if(p<1||q<1||p>n||q>m) continue;
			merge(i,j,p,q);
			d[(p-1)*m+q]++;
		}
	}
	int x=find(1),cnt=n*m;
	for(int i=2;i<=cnt;i++){
		if(find(i)!=x){
			puts("No");
			return;
		}
	}
	int res=0;
	for(int i=1;i<=cnt;i++){
		if(!d[i]) res++;
		if(res>1){
			puts("No");
			return;
		}
	}
	puts("Yes");
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
