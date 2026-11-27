// https://www.luogu.com.cn/problem/P9349
// 题意：有 N 颗棋子，初始第 i 颗颜色为 A_i。
// 从 i = 1 到 N 依次操作：
// 将第 i 颗放在第 i-1 颗右边（i=1 直接放桌上）；
// 若前 i-1 颗中存在当前颜色等于 A_i 的棋子，设最大下标为 j，
// 则将第 j+1..i-1 颗棋子全部涂成 A_i。
// 求全部操作结束后的最终颜色序列。
// 题意：输入 N 和 N 行 A_1..A_N；
// 输出 N 行表示最终每颗棋子的颜色。
// 数据范围：1 <= N <= 2 * 10^5，
// 1 <= A_i <= 10^9。
// 算法标签：贪心、模拟
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

int n,color[N];
map<int,int> last;

int main()
{
    cin>>n;
	for(int i=1;i<=n;i++){
        cin>>color[i];
		last[color[i]]=i;
	}
	for(int i=1;i<=n;i++){
		int lci=last[color[i]];
		for(int j=i+1;j<lci;j++)
            color[j]=color[i];
		i=lci;
	}
	for(int i=1;i<=n;i++)
        printf("%d\n",color[i]);
	return 0;
}
