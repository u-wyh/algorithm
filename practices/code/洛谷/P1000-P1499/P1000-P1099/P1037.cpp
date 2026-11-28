// https://www.luogu.com.cn/problem/P1037
// 题意：给十进制整数 n 和 k 条一位数字替换规则，每次可以按规则改一个位置，
// 允许反复改同一位。求可以得到多少个不同的整数，原数也算。
// 数据范围：n < 10^30，k ≤ 15，规则右侧不为 0。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索、数学

#include<bits/stdc++.h>
#define lll __uint128_t
using namespace std;
char a[39],k,x[19],y[19];
bool b[99];
int l,t;
lll s;
void out(lll x){//int128输出要自己写
	if(x>9)out(x/10);
	putchar(x%10+48);
}
void dfs(char c){
	if(b[c])return;//重复就退出
	b[c]=1;
	for(int i=0;i<k;i++)if(x[i]==c)dfs(y[i]);
}
int main(){
	scanf("%s%d",a,&k),l=strlen(a);
	for(int i=0;i<k;i++)cin>>x[i]>>y[i];
	dfs(a[0]),b[0]=0;//先搜索最高位，因为最高位不能为0
	for(char i='1';i<='9';i++)t+=b[i],b[i]=0;
	s=t,t=0;
	for(int i=1;i<l;i++){//搜索其余位
		dfs(a[i]);
		for(char i='0';i<='9';i++)t+=b[i],b[i]=0;
		s*=t,t=0;
	}
	out(s);
}
