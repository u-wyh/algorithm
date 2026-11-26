// https://www.luogu.com.cn/problem/P2779
// 题意：输入一个仅由字符 B、W、? 组成的非空字符串，其中 ? 表示颜色待定。
// 合法黑白序列定义为：任意正整数 n 个连续 B 接上 n 个连续 W 是合法序列，且两个合法序列拼接后仍合法，无其他合法序列。
// 将每个 ? 替换为 B 或 W（非 ? 位置不可修改），统计能得到合法序列的不同填法数量（至少一位不同即算不同）。
// 输出一个整数，为合法方案数对 10^9 + 9 取模的结果。
// 数据范围：对于 100% 的数据，字符串长度不超过 500000（长度大于 0），仅含 W、B、? 三种字符。
#include<bits/stdc++.h>
using namespace std;
const int p=1e9+9;
char str[500006];
int dp[500006]={1},n;
int main() {
    cin>>str+1;
    n=strlen(str+1);
    for(int i=1;i<=n;i++) {
    	if(str[i]!='W') {
    		int l=i,r=i+1;
    		for(int j=i;l>=1&&r<=n;j++) {
    			if(str[l]=='W'||str[r]=='B') break;
    			dp[r]=(dp[r]+dp[l-1])%p;
    			l--,r++;
			}
		}
	}
	cout<<dp[n];
    return 0;
}
