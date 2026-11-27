// https://www.luogu.com.cn/problem/P2585
// 题意：以字符串形式给出二叉树（0/1/2 表示子节点数），用红、绿、蓝染色。
// 要求父子节点颜色不同，且同一节点的两子节点颜色也不同。
// 输出最多和最少有多少个节点染成绿色。
// 数据范围：1 <= |s| <= 5*10^5。
#include<iostream>
#include<cstdio>
#include<cstring>
// 算法标签：树形动态规划、深度优先搜索
using namespace std;
const int N = 500050;
char s[N];
int dp[N][4], f[N][4], cnt;
int ans1 = 1;
void dfs(int x) {
	if (s[x] == '0') {//叶节点
		f[x][0] = dp[x][0] = 1;
		return;
	}
	dfs(++cnt);
    //左儿子编号为x+1
	if (s[x] == '1') { //一个儿子
		dp[x][0] = max(dp[x+1][1], dp[x+1][2])+1;
		dp[x][1] = max(dp[x+1][0], dp[x+1][2]);
		dp[x][2] = max(dp[x+1][0], dp[x+1][1]);
        	//儿子染另外一种颜色
		// 上方代码完全是复制一遍到下面
		f[x][0] = min(f[x+1][1], f[x+1][2])+1;
		f[x][1] = min(f[x+1][0], f[x+1][2]);
		f[x][2] = min(f[x+1][0], f[x+1][1]);
	}
	else {
        //右儿子编号为k
		int k = ++cnt;
		dfs(k);
		dp[x][0] = max(dp[x+1][1] + dp[k][2], dp[x+1][2] + dp[k][1]) + 1;
		dp[x][1] = max(dp[x+1][0] + dp[k][2], dp[x+1][2] + dp[k][0]);
		dp[x][2] = max(dp[x+1][0] + dp[k][1], dp[x+1][1] + dp[k][0]);

		f[x][0] = min(f[x+1][1] + f[k][2], f[x+1][2] + f[k][1]) + 1;
		f[x][1] = min(f[x+1][0] + f[k][2], f[x+1][2] + f[k][0]);
		f[x][2] = min(f[x+1][0] + f[k][1], f[x+1][1] + f[k][0]);
	}
	ans1 = max(ans1, dp[x][0]);
}
int main() {
	scanf ("%s", s + 1);
	dfs(++cnt);
	cout << ans1 << ' ' << min(f[1][0], min(f[1][1], f[1][2])) << endl;
	return 0;
}
