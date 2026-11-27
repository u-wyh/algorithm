// https://www.luogu.com.cn/problem/P2896
// 题意：输入奶牛数量 N，以及排成一队的每头奶牛卡片上的分组编号 D_i（1、2 或 3）。
// 不能重排奶牛顺序，只能修改某些奶牛身上的编号（仍为 1~3），使队伍编号序列按升序（111222333 形式）或降序（333222111 形式）排列。
// 求达成有序排列所需修改的最小次数。
// 输出一个整数，表示最少需要修改的奶牛编号数量。
// 数据范围：对于 100% 的数据，1 <= N <= 30000，1 <= D_i <= 3。
#include<iostream>
#include<cmath>
// 算法标签：动态规划、最长上升子序列
using namespace std;
int n,s,a[30005],f[30005],f1[30005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>0;j--){
			if(a[i]>=a[j])
			f[i]=max(f[i],f[j]);
			if(a[i]==a[j])break;//前面已经被处理过可以跳过
		}//内层倒序循环
		f[i]++;
	}//最长不下降序列
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>0;j--){
			if(a[i]<=a[j])
			f1[i]=max(f1[i],f1[j]);
			if(a[i]==a[j])break;
		}
		f1[i]++;
	}//最长不上升序列
	for(int i=1;i<=n;i++){
		s=max(s,f[i]);
		s=max(s,f1[i]);
	}
	cout<<n-s;
	return 0;
}
