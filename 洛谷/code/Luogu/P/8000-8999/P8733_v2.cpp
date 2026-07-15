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
