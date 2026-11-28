// https://www.luogu.com.cn/problem/P2935
// 题意：输入牧场数 P、贝茜喜欢的牧场数 F、双向路数 C，
// 随后 F 个喜欢的牧场编号以及 C 条双向路 (a_i, b_i, T_i)。
// 选择一个牧场作为起点，
// 使得该牧场到所有 F 个喜欢的牧场的最短通行时间平均值最小。
// 若存在多个最优牧场，取编号最小的那个。
// 输出一个整数，表示最佳牧场的编号。
// 数据范围：对于 100% 的数据，1 <= P <= 500，
// 1 <= F <= P，1 < C <= 8000，
// 1 <= a_i, b_i <= P
// 1 <= T_i < 892。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Floyd、传递闭包
#include<iostream>
#include<cstdio>
#define X 200+10
using namespace std;
int fa[X];
bool vis[X][X];              //用来标记白点
int main()
{
	int n,t,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>t;
		while(t!=0){
			vis[i][t]=1;
			cin>>t;
		}
	}
	for(int i=1;i<=n;++i)
        fa[i]=i;                 //并查集，让自己是自己爸爸
	for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(vis[i][j]||(vis[i][k]&&vis[k][j]))
                    vis[i][j]=1;              //标记白点
	for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(vis[i][j]==1)
                fa[j]=fa[i];
	for(int i=1;i<=n;++i)
        if(fa[i]==i)
            ans++;                     //累加光盘数
	printf("%d",ans);
	return 0;                  //大功告成，程序拜拜！
}
