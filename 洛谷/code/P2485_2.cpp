// https://www.luogu.com.cn/problem/P2485
#include<bits/stdc++.h>
using namespace std;
#define int long long

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

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

int bsgs(int a,int b,int p){
    a%=p;
    b%=p;
    // 如果b为1  直接特判
    if(b==1){
        return 0;
    }
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
    int T,k;
    cin>>T>>k;
    while(T--){
        int y,z,p;
        cin>>y>>z>>p;
        if(k==1){
            cout<<power(y,z,p)<<endl;
        }
        else if(k==2){
            exgcd(y,p);
            if(z%d!=0){
                cout<<"Orz, I cannot find x!"<<endl;
            }
            else{
                int dx=p/d;
                x=(__int128)(x%dx)*((z/d)%dx)%dx;
                x=(x+dx)%dx;
                cout<<x<<endl;
            }
        }
        else{
            int ans=bsgs(y,z,p);
            if(ans==-1){
                cout<<"Orz, I cannot find x!"<<endl;
            }
            else{
                cout<<ans<<endl;
            }
        }
    }
    return 0;
}