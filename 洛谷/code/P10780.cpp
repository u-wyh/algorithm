// https://www.luogu.com.cn/problem/P10780
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e4+7;
const int INV = 1668;

int comb(int n){
    return (n*(n-1)/2)%MOD;
}

signed main()
{
    string s;
    cin>>s;
    int n=0;
    int len=s.length();
    for(int i=0;i<len;i++){
        n=(n*10+s[i]-'0')%MOD;
    }

    int ans=INV;
    ans=(ans*n)%MOD;
    ans=(ans*(n+1))%MOD;
    ans=(ans*(n+2))%MOD;
    cout<<ans<<endl;
    return 0;
}