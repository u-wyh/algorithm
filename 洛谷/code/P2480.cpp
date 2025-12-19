#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=999911658;

LL n,G,farc[50010],a[5],b[5]={0,2,3,4679,35617},val;

// 原理来自，讲解098，乘法快速幂
// 计算a的b次方，最终 % mod 的结果
long long power(long long a, long long b, long long mod) {
	long ans = 1;
	while (b > 0) {
		if ((b & 1) == 1) {
			ans = multiply(ans, a, mod);
		}
		a = multiply(a, a, mod);
		b >>= 1;
	}
	return ans;
}

void init(LL p)//预处理
{
	farc[0]=1;
	for(LL i=1;i<=p;i++)
		farc[i]=farc[i-1]*i%p;
}

LL C(LL n,LL m,LL p)//组合数
{
	if(n<m) return 0;
	return farc[n]*fast_pow(farc[m],p-2,p)%p*power(farc[n-m],p-2,p)%p;
}

LL Lucas(LL n,LL m,LL p)//Lucas定理
{
	if(n<m) return 0;if(!n) return 1;
	return Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}

void CRT()//中国剩余定理
{
	for(LL i=1;i<=4;i++)
		val=(val+a[i]*(mod/b[i])%mod*power(mod/b[i],b[i]-2,b[i]))%mod;
}

int main()
{
	scanf("%lld%lld",&n,&G);
	if(G==(mod+1)){
		printf("0\n");
		return 0;
	}//特判
	for(LL k=1;k<=4;k++){
		init(b[k]);
		for(LL i=1;i*i<=n;i++){
			if(n%i==0){
				a[k]=(a[k]+Lucas(n,i,b[k]))%b[k];
				if(i*i!=n){
					a[k]=(a[k]+Lucas(n,n/i,b[k]))%b[k];
				}
			}
		}
	}//逐一枚举n的约数
	CRT();
	printf("%lld\n",power(G,val,mod+1));//注意mod要+1
	return 0;
}
