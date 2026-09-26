// https://www.luogu.com.cn/problem/P4454
#include<bits/stdc++.h>
using namespace std;
#define int long long

int g,p,a,b;

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

// 求解(a^x)%p=b的x最小取值是多少
// 要求gcd(a,p)=1 
int bsgs(int a,int b,int p){
    a%=p;
    b%=p;
    // 如果b为1  直接特判
    if(b==1){
        return 0;
    }
    
    // 这道题保证了不会出现这种情况，所以下面的这一段不需要写
    // 但是有的题目就很恶心 不给这个
    if(a==0){
        if(b==0) return 1;
        return -1;
    }

    map<int,int>mp;
    int t=ceil(sqrt((long double)p));

    // 枚举右边 b*a^B
    int now=b;
    for(int B=0;B<t;B++){
        // 保留最大的B
        mp[now]=B;
        now=(now*a)%p;
    }

    // 左边每次乘 a^t
    int at=power(a,t,p);
    now=1;
    // 枚举左边 a^(A*t)
    for(int A=0;A<=t;A++){
        if(mp.count(now)){
            int ans=A*t-mp[now];
            if(ans>=0){
                return ans;
            }
        }
        now=now*at%p;
    }

    return -1;
}

signed main()
{
    int T;
    cin>>g>>p>>T;
    while(T--){
        cin>>a>>b;
        a=bsgs(g,a,p);

        cout<<power(b,a,p)<<endl;
    }
    return 0;
}