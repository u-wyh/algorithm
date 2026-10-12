// 用途：求 a^x≡b (mod p) 的最小非负 x。
// 时间：O(√p log p)。
// 空间：O(√p)。
// 注意：要求 gcd(a,p)=1；哈希或映射表存根号级状态。
// 例题：https://www.luogu.com.cn/problem/P3846
// 题意：求最小非负整数 x，使 a^x 与 b 模 p 同余。
// 思路：把指数拆为大步和小步，哈希表匹配两边的幂。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int p,a,b;

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=(__int128)ans*a%mod;
        }
        b>>=1;
        a=(__int128)a*a%mod;
    }
    return ans;
}

// 拆分指数为 A*t-B，记录同余值对应的最大 B。
int bsgs(int a,int b,int p){
    a%=p;
    b%=p;
    if(b==1){
        return 0;
    }
    
    if(a==0){
        if(b==0) return 1;
        return -1;
    }

    map<int,int>mp;
    int t=ceil(sqrt((long double)p));

    int now=b;
    for(int B=0;B<t;B++){
        mp[now]=B;
        now=(__int128)now*a%p;
    }

    int at=power(a,t,p);
    now=1;
    for(int A=0;A<=t;A++){
        if(mp.count(now)){
            int ans=A*t-mp[now];
            if(ans>=0){
                return ans;
            }
        }
        now=(__int128)now*at%p;
    }

    return -1;
}

signed main()
{
    cin>>p>>a>>b;
    int ans=bsgs(a,b,p);
    if(ans==-1){
        cout<<"no solution"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}
