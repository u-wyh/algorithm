// https://www.luogu.com.cn/problem/B3903
// 题意：给 n 个 2 的整数次幂和上限 x。
// 重新排列这 n 个元素，使任意相邻两项之和都不超过 x。
// 按原下标区分元素，求可行排列数，对 10^9+7 取模。
// 数据范围：2 ≤ n ≤ 10^5，1 ≤ a[i] ≤ 2^60，
// 1 ≤ x < 2^63。
// 难度评分：1800（洛谷分级换算）
// 算法标签：组合数学、快速幂、乘法逆元

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n,x,tmp;
int a,b,c,d;
int fac[MAXN];
int inv[MAXN];
int val[MAXN];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void build(){
    fac[0]=1;
    for(int i=1;i<=n+1;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n+1]=power(fac[n+1],MOD-2);
    for(int i=n;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

void prepare(){
    tmp=x;
    while((tmp-(tmp&(-tmp)))){
        tmp-=tmp&(-tmp);
    }
    for(int i=1;i<=n;i++){
        if(val[i]==tmp){
            a++;
        }
        else if(val[i]+tmp>x){
            b++;
        }
        else{
            c++;
        }
        if(val[i]>=x){
            d++;
        }
    }
}

int comb(int n,int m){
    return fac[n]*inv[n-m]%MOD*inv[m]%MOD;
}

signed main()
{
    n=read(),x=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build();
    prepare();
    if(d||(a>c+1)){
        cout<<0<<endl;
        return 0;
    }
    if(tmp==x){
        cout<<fac[n]<<endl;
        return 0;
    }
    // a 类各占一个 c 类间隔，b 类只能放在余下的间隔中。
    int gaps=c+1-a;
    if(gaps==0&&b>0){
        cout<<0<<endl;
        return 0;
    }
    int ans=fac[a]*fac[b]%MOD*fac[c]%MOD*comb(c+1,a)%MOD;
    if(gaps>0){
        ans=ans*comb(b+gaps-1,b)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}