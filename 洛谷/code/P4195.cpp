// https://www.luogu.com.cn/problem/P4195
// exBSGS主要解决：给出 a、b、mod，求满足 a^x=b (mod mod) 的最小非负整数x
//
// 普通BSGS要求 gcd(a,mod)=1
// 如果 gcd(a,mod)!=1，那么需要先不断消掉a和mod之间的公因子
//
// 原式：
// a^x=b (mod mod)
//
// 设 d=gcd(a,mod)
// 如果 b%d!=0，那么一定无解
//
// 如果可以约掉d：
// mod/=d
// b/=d
//
// 但是a除掉d之后还会留下一个 a/d
// 所以用k记录这些留下来的系数
//
// 消掉cnt次之后：
// k*a^(x-cnt)=b (mod mod)
//
// 当 gcd(a,mod)=1 时：
// a^(x-cnt)=b*k^(-1) (mod mod)
//
// 然后使用普通BSGS求出 x-cnt
// 最后答案加上cnt
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

// 求解(a^x)%p=b的x最小取值是多少
// 要求gcd(a,p)=1 
int bsgs(int a,int b,int p){
    a%=p;
    b%=p;
    // 如果b为1  直接特判
    if(b==1){
        return 0;
    }
    
    int t=ceil(sqrt((long double)p));

    unordered_map<int,int>mp;
    // 减少unordered_map扩容和冲突 常数优化
    mp.reserve(t*2);
    mp.max_load_factor(0.7);

    // 枚举右边 b*a^B
    int now=b;
    for(int B=0;B<t;B++){
        // 保留最大的B
        mp[now]=B;
        now=(now*a)%p;
    }

    // 左边每次乘 a^t
    int at=1;
    for(int i=1;i<=t;i++){
        at=at*a%p;
    }

    now=1;
    // 枚举左边 a^(A*t)
    for(int A=0;A<=t;A++){
        auto it=mp.find(now);
        if(it!=mp.end()){
            int ans=A*t-it->second;
            if(ans>=0){
                return ans;
            }
        }
        now=now*at%p;
    }

    return -1;
}

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
        k=k*(a/d)%mod;
        cnt++;
        if(k==b){
            return cnt;
        }
    }

    // k*a^(x-cnt)=b
    // a^(x-cnt)=b*k^(-1)
    b=b*inv(k,mod)%mod;
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