// https://www.luogu.com.cn/problem/P1252
// 题意：5 名队员参加 25 km 接力赛，
// 每人跑一次且跑 [1, 10] 内的整数公里数。
// 题意：已知每人连续跑 1..10 km 的各自用时（单位公里用时不加快），
// 求最短总用时及分配方案。
// 输入：共 5 行，
// 每行 10 个正整数表示该队员连续跑 1..10 km 的总用时。
// 输出：第一行输出最短总用时，
// 第二行输出 5 个整数表示 1..5 号队员各自跑的公里数。
// 数据范围：固定 5 人总长 25 km，每项时间均为不超过 10^7 的正整数。
// 难度评分：1000（洛谷分级换算）
// 算法标签：深度优先搜索、剪枝
#include<bits/stdc++.h>
using namespace std;

int a[100][100],minn=INT_MAX,q[100],i,j,f[1000][100],qmin[100];//数组是我随手开的
void dfs(int x,int y,int s){//搜索内容 x代表还剩 x km,y代表前y人,s代表最少时间
	if (x<0)
	return;//这句话可能是多余的
	if (f[x][y]<=s)
	return;
	f[x][y]=s;//记忆化，f[x][y]表示还剩x公里，前y个人参加，能达到的最小的时间
	if (y>5){//如果所有人都跑了
		if (x==0)//如果跑完全程了
			if (minn>s){//如果时间比原来已记录的少
				minn=s;
				for (int i=1;i<=5;++i)
				qmin[i]=q[i];//记录
			}
		 return;
	}
	for (int i=1;i<=min(x,10);++i){//枚举当前这个人跑了i公里
	q[y]=i;//记录
	dfs(x-i,y+1,s+a[y][i])//;剩下路程-i,下一个人，时间加该人跑i公里所需要的时间
}
}
int main(){
	for (i=1;i<=5;++i)
	for (j=1;j<=10;++j)
	cin>>a[i][j];//输入
	for (i=0;i<=100;++i)
	for (j=0;j<=80;++j)
	f[i][j]=INT_MAX;//初始化，我也是随手写的
	dfs(25,1,0);//搜索
	cout<<minn<<endl;
	for (i=1;i<=4;++i)
	cout<<qmin[i]<<" ";cout<<qmin[5];//打印答案
}
