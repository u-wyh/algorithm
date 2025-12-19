// https://www.luogu.com.cn/problem/P2155
//给定n、m  求出在1~n!中与m!互质的元素的个数
//题目中已经限定了m<=n  那么一定有 m!|n!
//通过辗转相除法  我们可以知道gcd(a,b)=gcd(a+k*b,b) 其中k是大于等于0的整数
//那么也就是说 gcd(x,m!)=gcd(x+k*m!,m!)  x属于1~m!  k属于0~n!/m!
//意思是  对于1~m!   m!+1~2*m!  2*m!+1~3*m!  ...   n!-m!+1 ~ n!((n!/m!-1)*m!+1 ~ (n!/m!)*m!)
//这些区间上与m!互质的数字的个数是一样的  区间的个数是n!/m!
//也就是说答案就是  (n!/m!)*(m!的欧拉函数)
//经过推演知道：
//n为合数时  f(n)=n*f(n-1)
//n为素数时  f(n)=(n-1)*f(n-1)
// 代码有点小问题 还没有搞好  见hack数据（下面）
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int mod;

bool isprime[MAXN];
int prime[MAXN];

int fac[MAXN];
int phi[MAXN];//记录i!的欧拉函数值

void prepare(int n){
    int cnt=0;
    isprime[0]=isprime[1]=1;
    for(int i=2;i<=n;i++){
        if(isprime[i]==0){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            isprime[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
    fac[0]=phi[0]=1;
    for(int i=1;i<=n;i++){
        int tmp=i;
        while(tmp%mod==0){
            tmp/=mod;
        }
        fac[i]=fac[i-1]*i%mod;
        tmp=i-1+isprime[i];
        while(tmp%mod==0){
            tmp/=mod;
        }
        phi[i]=phi[i-1]*tmp%mod;
    }
}

//单个数字求欧拉函数值
int geteuler(int n){
	int ans=1;
	int tmp=n;
	for(int i=2;i*i<=tmp;i++){
		if(tmp%i){
			continue;
		}
		ans*=(i-1);
		tmp/=i;
		while(tmp%i==0){
			ans*=i;
			tmp/=i;
		}
	}
	if(tmp>1){
		ans*=(tmp-1);
	}
	return ans;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T>>mod;
    prepare(10000000);
    while(T--){
        int n,m;
        cin>>n>>m;
        int ans=fac[n]*phi[m]%mod*power(fac[m],mod-2)%mod;
        if(n/mod>m/mod){
            ans=0;
        }
        cout<<ans<<endl;
    }
    return 0;
}
/*
hack:
1 3
4 3
ans:1
*/