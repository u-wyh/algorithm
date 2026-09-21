// https://www.luogu.com.cn/problem/P2260
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19940417;
const int INV2 = 9970209;
const int INV6 = 3323403;

int n,m;

int query(int n){
    int ans=0;
    ans=(n*n)%MOD;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;

        int tmp=(((v*(lt+rt))%MOD)*(((rt-lt+1)*INV2)%MOD))%MOD;
        ans=(ans-tmp+MOD)%MOD;
    }
    return ans;
}

int getval(int x){
    return (((x*(x+1))%MOD)*(((2*x+1)*INV6)%MOD))%MOD;
}

int getsum(int l,int r){
    return (getval(r)-getval(l-1)+MOD)%MOD;
}

int query(int n,int m){
    int limit=min(n,m);
    int ans=0;
    for(int lt=1,rt;lt<=limit;lt=rt+1){
        int a=n/lt;
        int b=m/lt;

        rt=min(n/a,m/b);
        rt=min(rt,limit);

        int tmp=0;
        tmp+=(((n*m)%MOD)*(rt-lt+1))%MOD;
        int t1=((((lt+rt)*(rt-lt+1))%MOD)*INV2)%MOD;
        tmp=(tmp-((((n*b)%MOD)*t1)%MOD)+MOD)%MOD;
        tmp=(tmp-((((m*a)%MOD)*t1)%MOD)+MOD)%MOD;

        tmp=(tmp+((((a*b)%MOD)*getsum(lt,rt))%MOD))%MOD;
        ans=(ans+tmp)%MOD;
    }
    return ans;
}

signed main()
{
    cin>>n>>m;
    int ans1=query(n);
    int ans2=query(m);
    int ans3=query(n,m);
    int ans=(((ans1*ans2)%MOD)-ans3+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}