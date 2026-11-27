// https://www.luogu.com.cn/problem/P2396
// 题意：有 n 张卡片（数字 a_i），每次选一张向前走 a_i 步并丢弃，
// 用完卡片获胜。
// 若途中停在 m 个厄运数字之一（含终点）则失败。
// 输出获胜的方案数对 10^9+7 取模的结果。
// 数据范围：n <= 24，0 <= m <= 2，
// 1 <= a_i, b_i <= 10^9。
// 算法标签：状态压缩DP、位运算
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m;
int dis[1<<24];//表示在状态i下，走到哪个位置
bool ok[1<<24];//表示在状态i下，走到的位置是否有效
int bad[2];//表示厄运数字
int dp[1<<24];//表示在i的情况下有多少种方案

int main()
{
    //cout<<change(16)<<' '<<change(64)<<' '<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>dis[1<<i];
    }
    cin>>m;
    for(int i=0;i<m;i++){
        cin>>bad[i];
    }
    //完成输入与输出

    dis[0]=0;
    for(int s=1;s<(1<<n); s++){
        int j=s&-s,k=s;
        dis[s]=dis[s^j]+dis[j];//子集和自己的补集  补集一定是只含有最右边的那个1
		ok[s]=true;
		for(int i=0;i<m;i++){
            if(dis[s]==bad[i]){
                ok[s]=false;
                break;
            }
		}
	}
	//完成dis  ok数组的初始化

	dp[0]=1;
	for(int s=1;s<(1<<n);s++){
        int k=s;
        while(k&&ok[s]){
            int j = k & -k; //j是当前找到的lowbit
            dp[s] = (dp[s] + dp[s ^ j])%MOD;
            k ^= j; //k中去掉这个"1"，这样下次lowbit会找到另一个"1"
        }
	}
	cout<<dp[(1<<n)-1]<<endl;
    return 0;
}
