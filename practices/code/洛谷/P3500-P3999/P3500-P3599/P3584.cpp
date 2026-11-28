// https://www.luogu.com.cn/problem/P3584
// 题意：输入人数及食物数
// n（围成一圈，第 i 人在食物 i 与 i+1 间，
// 第 n 人在 n 与 1 间），
// 以及每份食物的热量 c_1..c_n。
// 每人选左或右的食物，两人选同一份则平分热量；
// 若在他人选择不变时某人改选另一份能获得严格更多热量则会不满意。
// 若无合法分配输出 NIE；
// 否则输出 n 个整数表示每人所选食物编号（任一合法解）。
// 数据范围：2 <= n <= 10^6，1 <= c_i <= 10^9。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、破环成链
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
int dp[MAXN][5];//表示这个食物被左边吃  右边吃  一起吃  没人吃  以及转移过来的状态
int ans[MAXN];

bool check(int x){
    for(int i=1;i<=n+1;i++){
        dp[i][1]=dp[i][2]=dp[i][3]=dp[i][4]=0;
    }
    dp[1][x]=1;
    for(int i=2;i<=n+1;i++){
        if(dp[i-1][1] && arr[i-1]<=arr[i]*2)
			dp[i][1]=1;
		if(dp[i-1][1] && arr[i-1]<=arr[i])
			dp[i][3]=1;

		if(dp[i-1][2] && arr[i]<=arr[i-1]*2)
			dp[i][2]=2;
		if(dp[i-1][2] && arr[i]<=arr[i-1])
			dp[i][4]=2;

		if(dp[i-1][3] && arr[i]<=arr[i-1])
			dp[i][2]=3;
		if(dp[i-1][3] && arr[i]*2<=arr[i-1])
			dp[i][4]=3;

		if(dp[i-1][4] && arr[i-1]<=arr[i])
			dp[i][1]=4;
		if(dp[i-1][4] && arr[i-1]*2<=arr[i])
			dp[i][3]=4;
    }
    return dp[n+1][x];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    arr[n+1]=arr[1];//将环改成链
    for(int i=1;i<=4;i++){
        //枚举第一个蛋糕的状态
        if(check(i)){
            int m=i;
            for(int j=n+1;j>=1;j--){
                if(m==1){
                    //这个蛋糕是被左边吃
                    ans[j-1]=(j-1)%n+1;
                }
                else if(m==2){
                    //这个蛋糕是被右边吃
                    ans[j]=(j-1)%n+1;
                }
                else if(m==3){
                    ans[j]=ans[j-1]=(j-1)%n+1;
                }
                m=dp[j][m];//转移状态
            }
            for(int i=1;i<=n;i++){
                cout<<ans[i]<<' ';
            }
            return 0;
        }
    }
    cout<<"NIE"<<endl;
    return 0;
}
