// https://www.luogu.com.cn/problem/P3449
// 题意：输入回文串数量 n，
// 以及 n 个互不相同的回文串（每行给出长度 a_i 和字符串本身）。
// 将这 n 个串任意两两拼接
// （允许自己拼自己，ab 与 ba 视作不同组合共 n^2 个新串），
// 统计其中仍是回文串的个数。
// 输出一个整数，表示满足条件的新回文串数量。
// 数据范围：n >= 2，串仅含小写字母且两两不同，
// 所有回文串总长度不超过 2*10^6。
// 难度评分：1500（洛谷分级换算）
// 算法标签：字符串哈希、快速幂
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