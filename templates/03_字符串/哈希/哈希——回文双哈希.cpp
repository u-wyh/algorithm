// https://www.luogu.com.cn/problem/P3449
//这道题最关键的是这个核心公式的推导   并且需要使用双哈希
// 第一个字符串哈希值为a  长度为s   第二个字符串哈希值为b  长度为t
// 由于是回文串  那么有a*(p^t)+b=b*(p^s)+a
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int BASE = 131;
const int MOD = 1e9+7;
const int BASE2 = 131;
const int MOD2 = 1e9+9;
const int MAXN = 2e6+5;

int n,m;
int h[MAXN];
int f[MAXN];
int g[MAXN];

int h2[MAXN];
int f2[MAXN];
int g2[MAXN];

char s[MAXN];
map<int,int>t;
map<int,int>t2;

int power(int a,int b,int mod){
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

int gethash(){
    int ans=s[1]-'a'+1;
    for(int i=2;i<=n;i++){
        ans=(ans*BASE+s[i]-'a'+1)%MOD;
    }
    return ans;
}

int gethash2(){
    int ans=s[1]-'a'+1;
    for(int i=2;i<=n;i++){
        ans=(ans*BASE2+s[i]-'a'+1)%MOD2;
    }
    return ans;
}

signed main()
{
    scanf("%lld",&m);
    for(int i=1;i<=m;i++){
        scanf("%lld %s",&n,s+1);
        h[i]=gethash();
        f[i]=power(power(BASE,n,MOD)-1,MOD-2,MOD);
        g[i]=(h[i]*f[i])%MOD;
        t[g[i]]++;

        h2[i]=gethash2();
        f2[i]=power(power(BASE2,n,MOD2)-1,MOD2-2,MOD2);
        g2[i]=(h2[i]*f2[i])%MOD2;
        t2[g2[i]]++;
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        ans+=min(t[g[i]],t2[g2[i]]);
    }
    cout<<ans<<endl;
    return 0;
}