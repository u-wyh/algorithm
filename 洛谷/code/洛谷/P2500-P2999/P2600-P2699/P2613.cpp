// https://www.luogu.com.cn/problem/P2613
// 题意：给定两个大整数 a 和 b，
// 求同余方程 bx = a (mod 19260817) 的最小非负整数解。
// 若无解输出 Angry!。
// 数据范围：0 <= a <= 10^10001，
// 1 <= b <= 10^10001，a, b 不
// 同时为 19260817 的倍数。
// 算法标签：扩展欧几里得算法、数论
#include <cstdio>
#include <cmath>
using namespace std;
#define MOD 19260817

long long a,b,x,y,d,k;
long long read() {
	long long ans=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') ans=(ans*10+c-'0')%MOD,c=getchar();
	return ans;
}
long long exgcd(long long a,long long b) {
	if(b==0) {
		x=1,y=0;
		return a;
	}
	long long d=exgcd(b,a%b);
	long long z=x;
	x=y;
	y=z-y*(a/b);
	return d;
}
int main() {
	a=read();
	b=read();
	d=exgcd(b,MOD);
	if(a%d!=0) printf("Angry!");
	else printf("%lld",((x*a/d%MOD)+MOD)%MOD);
	return 0;
}
