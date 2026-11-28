// https://www.luogu.com.cn/problem/P1375
// 题意：有 2n 只猫围成一圈，给每只猫找一只伙伴，用绳连接同一对。
// 不同绳子不能交叉，统计按位置区分的配对方案数，并对 10^9+7 取模。
// 数据范围：1 ≤ n ≤ 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：卡特兰数、组合数学、快速幂

#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;

long long fac[MAXN];
long long inv[MAXN];

long long power(long long x, long long p) {
	long long ans = 1;
	while (p > 0) {
		if ((p & 1) == 1) {
			ans = (ans * x) % MOD;
		}
		x = (x * x) % MOD;
		p >>= 1;
	}
	return ans;
}
void build(int n){
    fac[1]=1,fac[0]=1;
    inv[0]=1;
    for(int i=2;i<=n;i++){
        fac[i]=(i*fac[i-1])%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>0;i--){
        inv[i]=((i+1)*inv[i+1])%MOD;
    }
}

long long c(int n,int k){
    return ((fac[n]*inv[k])%MOD*inv[n-k])%MOD;
}

int main()
{
    int n;
    cin>>n;
    build(2*n);
    cout<<((c(2*n,n)-c(2*n,n-1))%MOD+MOD)%MOD;
    return 0;
}
