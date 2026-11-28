// https://www.luogu.com.cn/problem/P8733
// 题意：输入 n, D 和 n 个村庄坐标
// (x_i, y_i)
// （两点距离为欧氏距离
// sqrt((x_i-x_j)^2+(y_i-y_j)^2)）；
// 从 1 号村庄出发，
// 每次直飞距离不能超过 D（可在任意经过村庄含 1 号加满油），
// 遍历所有村庄至少一次并回到 1 号村庄
// 输出最短总飞行距离（四舍五入保留 2 位小数）。
// 数据范围：1 <= n <= 20，1 <= x_i, y_i <= 10^4，
// 1 <= D <= 10^5。
// 难度评分：1700（洛谷分级换算）
// 算法标签：状态压缩动态规划、最短路
#include <bits/stdc++.h>
using namespace std ;
int n , d ;
double ans = DBL_MAX , x[25] , y[25] , dp[1 << 20][25] , dis[25][25] ;
bool vis[25] ;
double jl(int a , int b)
{
	return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b])) ;
}
int main()
{
	memset(dp , 0x7f , sizeof dp) ;
	memset(dis , 0x7f , sizeof dis) ;
	cin >> n >> d ;
	for(int i = 0 ; i < n ; i++)
        cin >> x[i] >> y[i] ;
	for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            if(jl(i , j) < d)
                dis[i][j] = jl(i , j) ;
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			for(int k = 0 ; k < n ; k++)
				dis[i][j] = min(dis[i][j] , dis[i][k] + dis[k][j]) ;
	dp[1][0] = 0 ;
	for(int i = 1 ; i < (1 << n) ; i++){
		for(int j = 0 ; j < n ; j++){
			if(!((i >> j) & 1))
				continue ;
			int tmp = i ^ (1 << j) ;
			for(int k = 0 ; k < n ; k++){
				if(!((tmp >> k) & 1))
					continue ;
				dp[i][j] = min(dp[i][j] , dp[tmp][k] + dis[j][k]) ;
			}
		}
	}
	for(int i = 1 ; i < n ; i++)
		ans = min(ans , dp[(1 << n) - 1][i] + dis[i][0]) ;
	printf("%.2lf" , ans) ;
	return 0 ;
}
