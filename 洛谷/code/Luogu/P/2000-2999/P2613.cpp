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
