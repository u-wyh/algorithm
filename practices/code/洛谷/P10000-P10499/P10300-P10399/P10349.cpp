// https://www.luogu.com.cn/problem/P10349
// 题意：有 n 只蚂蚁，第 i 只位于数轴坐标 i。
// 它们同时按初始方向以单位速度出发，两只相撞就各自掉头。
// 按编号输出每只蚂蚁最终的碰撞次数。
// 数据范围：1 ≤ n ≤ 3 × 10^5，
// 方向串长为 n，L 表示左、P 表示右。
// 难度评分：1200（洛谷分级换算）
// 算法标签：前缀和、后缀和

#include<iostream>
using namespace std;
int n,lans,rans,l[300001],r[300001];
char c[300001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
        cin>>c[i];
	for(int i=1;i<=n;i++){
		l[i]=lans;
		if(c[i]=='P')
            lans++;
	}
	for(int i=n;i>=1;i--){
		r[i]=rans;
		if(c[i]=='L')
            rans++;
	}
	for(int i=1;i<=n;i++){
		if(l[i]==r[i])
            cout<<l[i]+r[i];
		else if(l[i]<r[i]){
			if(c[i]=='L')cout<<l[i]*2;
			else cout<<l[i]*2+1;
		}
		else{
			if(c[i]=='P')cout<<r[i]*2;
			else cout<<r[i]*2+1;
		}
		cout<<" ";
	}
	return 0;
}
