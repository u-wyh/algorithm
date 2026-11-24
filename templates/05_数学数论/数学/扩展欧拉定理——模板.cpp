// https://www.luogu.com.cn/problem/P1405
//代码有一点问题
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1234570;

int n;
int nums[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int power(int a,int b,int mod){
    a%=mod,b%=mod;
    a=(a+mod)%mod;
    b=(b+mod)%mod;
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}

int geteuler(int n){
    if(n==0){
        return 0;
    }
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

int exeuler(int u,int mod){
    if(u==n+1){
        return 1;
    }
    else{
        int m=geteuler(mod);
        int tmp=exeuler(u+1,m);
        if(tmp>=m){
            tmp=tmp+m;
        }
        return power(nums[u],tmp,mod);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    int ans=power(nums[1],exeuler(2,geteuler(10007)),10007);
    cout<<ans<<endl;
    return 0;
}