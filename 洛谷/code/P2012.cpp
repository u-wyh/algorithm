// https://www.luogu.com.cn/problem/P2012
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    int n;
    while(cin>>n&&n){
        if(n<4){
            cout<<0<<endl;
            continue;
        }

        int a=power(4,n-4);
        int b=power(3,n);
        int c=power(2,n);
        int ans=0;
        if((n&1)==0){
            ans=1;
        }
        else{
            ans=-1;
        }
        ans+=6;
        ans=(ans+b)%MOD;
        ans=(ans-4*c)%MOD;
        ans=(ans+MOD)%MOD;
        ans=(ans*a)%MOD;

        cout<<ans<<endl;
    }
    return 0;
}