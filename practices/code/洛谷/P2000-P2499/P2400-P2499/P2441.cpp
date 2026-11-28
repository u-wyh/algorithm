// https://www.luogu.com.cn/problem/P2441
// 题意：n 个节点组成有根树，每个节点有正整数权值 a_i，共 k 次操作。
// 1 u：询问离 u 最近
// 且与 u 有大于 1 的公因数的祖先节点（无则输出 -1）。
// 2 u a：将节点 u 的权值修改为 a。
// 对每个 1 操作输出一行答案。
// 数据范围：n <= 2*10^5，k < 10^5，
// 修改次数 <= 50，a_i <= 2^31-1。
// 难度评分：1400（洛谷分级换算）
// 算法标签：深度优先搜索、最大公约数
#include<bits/stdc++.h>
using namespace std;
int a[200001]={0};
int fa[200001]={0};  // father 数组
int dfs(int x,int y){     //搜索。
	if(x == 0) return -1;
	if(__gcd(a[x],a[y]) > 1) return x;  //偷一下懒~直接使用gcd函数。
	return dfs(fa[x],y);
}
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++){
		int x,y;
		cin>>x>>y;
		fa[y]=x;  //建树
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x;
		if(x==1){
			cin>>y;
			cout<<dfs(fa[y],y)<<endl;  //搜索
		}
		else{
			cin>>x>>y;
			a[x]=y;
		}
	}
	return 0;
}
