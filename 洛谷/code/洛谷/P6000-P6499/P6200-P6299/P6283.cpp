// https://www.luogu.com.cn/problem/P6283
// 题意：平面上有 N 个自旋为 (x_i, y_i) 的粒子，
// 若 x_i <= x_j 且 y_i <= y_j 则两粒子可相互作用并使
// 其中一个消失。
// 求任意次相互作用后剩余粒子的最小数量。
// 数据范围：1 <= N <= 10^5，
// -10^9 <= x_i, y_i <= 10^9，各粒子自旋互不相同。
// 算法标签：排序、贪心
#include<bits/stdc++.h>
using namespace std;
const int maxn=100100;
int n;
int l[maxn],r[maxn];
struct node{
	int x,y;
	bool operator<(node u)const{
		return y==u.y?x<u.x:y<u.y;
	}//与前面差不多的排序，但是y坐标相同时x坐标需改成从小到大
}moo[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&moo[i].x,&moo[i].y);
	}
	stable_sort(moo+1,moo+1+n);
	l[1]=moo[1].x;
	for(int i=2;i<=n;i++){
		l[i]=min(l[i-1],moo[i].x);
	}//处理l
	r[n]=moo[n].x;
	for(int i=n-1;i>=1;i--){
		r[i]=max(r[i+1],moo[i].x);
	}//处理r
	int ans=1;//这里ans的初始值需要赋为1
	for(int i=1;i<n;i++){
		if(l[i]>r[i+1]){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
