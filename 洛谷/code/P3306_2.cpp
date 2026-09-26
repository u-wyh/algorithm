// https://www.luogu.com.cn/problem/P3306
#include<bits/stdc++.h>
using namespace std;
#define int long long

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=((__int128)ans*a)%mod;
        }
        b>>=1;
        a=((__int128)a*a)%mod;
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
        now=((__int128)now*a)%p;
    }

    // 左边每次乘 a^t
    int at=power(a,t,p);
    now=1;
    // 枚举左边 a^(A*t)
    for(int A=0;A<=t;A++){
        if(mp.count(now)){
            int ans=(__int128)A*t-mp[now];
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
    int p,a,b,x1,t;
    int T;
    cin>>T;
    while(T--){
        cin>>p>>a>>b>>x1>>t;
        if(t==x1){
            cout<<1<<endl;
            continue;
        }
        if(a==1){
            if(b==0){
                cout<<-1<<endl;
            }
            else{
                int ans=(t-x1+p)%p;
                ans=ans*power(b,p-2,p)%p;
                cout<<ans+1<<endl;
            }
            continue;
        }
        if(a==0){
            if(b==t){
                cout<<2<<endl;
            }
            else{
                cout<<-1<<endl;
            }
            continue;
        }
        if((x1*(a-1)+b)%p==0){
            cout<<-1<<endl;
            continue;
        }
        int ans=bsgs(a,(((b+t*(a-1))%p)*power(x1*(a-1)+b,p-2,p))%p,p);
        if(ans!=-1){
            ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}