// 用途：求一般模数下 a^x≡b 的最小非负 x。
// 时间：期望 O(√p)。
// 空间：O(√p)。
// 注意：允许 gcd(a,p)>1；输入 0 0 0 结束。
// 例题：https://www.luogu.com.cn/problem/P4195
// 题意：模数可不与底数互质时，求最小离散对数。
// 思路：先逐步约去 gcd 并累计指数，再在互质部分运行 BSGS。
#include<bits/stdc++.h>
using namespace std;
#define int long long

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

int inv(int a,int mod){
    exgcd(a,mod);
    return (x%mod+mod)%mod;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int bsgs(int a,int b,int p){
    a%=p;
    b%=p;
    if(b==1){
        return 0;
    }
    
    int t=ceil(sqrt((long double)p));

    unordered_map<int,int>mp;
    mp.reserve(t*2);
    mp.max_load_factor(0.7);

    int now=b;
    for(int B=0;B<t;B++){
        mp[now]=B;
        now=(__int128)now*a%p;
    }

    int at=1;
    for(int i=1;i<=t;i++){
        at=(__int128)at*a%p;
    }

    now=1;
    for(int A=0;A<=t;A++){
        auto it=mp.find(now);
        if(it!=mp.end()){
            int ans=A*t-it->second;
            if(ans>=0){
                return ans;
            }
        }
        now=(__int128)now*at%p;
    }

    return -1;
}

// 先消去 a 与模数的公因子，再调用普通 BSGS。
int exbsgs(int a,int b,int mod){
    if(mod==1){
        return 0;
    }

    a%=mod;
    b%=mod;
    if(b==1){
        return 0;
    }

    int cnt=0;
    int k=1;

    while((d=gcd(a,mod))!=1){
        if(b%d!=0){
            return -1;
        }

        mod/=d;
        b/=d;
        k=(__int128)k*(a/d)%mod;
        cnt++;
        if(k==b){
            return cnt;
        }
    }

    b=(__int128)b*inv(k,mod)%mod;
    int ans=bsgs(a,b,mod);

    if(ans==-1){
        return -1;
    }

    return ans+cnt;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int a,b,p;
    while(cin>>a>>p>>b){
        if(a==0&&b==0&&p==0){
            break;
        }

        int ans=exbsgs(a,b,p);

        if(ans==-1){
            cout<<"No Solution\n";
        }
        else{
            cout<<ans<<"\n";
        }
    }
    return 0;
}
