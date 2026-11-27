// https://www.luogu.com.cn/problem/P4305
// 题意：多组数据，每组给 n 个整数，去掉重复数字，只保留每个数第一次出现的位置并按原序输出。
// 数据范围：1 <= T <= 50，1 <= n <= 5e4，数值在 32 位有符号整数范围内。
#include<bits/stdc++.h>
// 算法标签：哈希表

#define For(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
inline int read()
{
	char c=getchar();int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-48;
	return x*f;
}
int T,n,x;
unordered_map<int,bool>s;//定义
void work()
{
	s.clear();//清空
	n=read();
	For(i,1,n){
		x=read();
		if(!s[x]){//没有的话，直接输出+标记掉。
			printf("%d ",x);
			s[x]=1;
		}
	}puts("");//换行
}
int main()
{
	T=read();
	while(T--)work();
	return 0;
}
