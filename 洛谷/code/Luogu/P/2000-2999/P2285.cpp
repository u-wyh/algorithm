#include <bits/stdc++.h>
using namespace std;
const int M = 1e4+5;

int n,m,dp[M],ans;
struct node{
	int t,x,y;
}a[M];//存位置结构体

int main()
{
	cin >> n >> m;
	for ( int i = 1;i <= m; i++ )
	{
		dp[i] = 1;//开始，所有位置都能达到它自己
		scanf ("%d%d%d",&a[i].t,&a[i].x,&a[i].y);
	}
	for ( int i = m; i > 1; i-- )
	    for ( int j = i-1; j >= 1; j-- )
	    {
	    	if (a[i].t-a[j].t>=abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y))
	    	{
	    		dp[j] = max(dp[i]+1,dp[j]);
	    		//若在规定时间内i能达到j，dp更新
			}
		}
	for ( int i = 1; i <= m; i++ )
	{
	    ans = max(dp[i],ans);
	    //结果取最大值，达到点最多
	}
	printf ("%d",ans);//输出
	return 0;
}
