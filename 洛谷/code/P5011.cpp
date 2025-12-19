#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19491001;

int n,k;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar(),x%=MOD;
    return x*f;
}

bool isprime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    // cout<<isprime(MOD);
    n=read();
    k=read();
    int sum=0;
    for(int i=1;i<=k;i++){
        int val=read();
        sum=(sum+val)%MOD;
    }
    int ans=(((n*power(k,MOD-2)%MOD+(2*(n-1)*power(k*k%MOD,MOD-2)%MOD))%MOD*sum)%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}