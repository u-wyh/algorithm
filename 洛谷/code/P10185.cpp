#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 2e5+5;

int n;
int arr[MAXN];
int val[MAXN];
int sum;
int ans;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int power(int a, int b) {
    int ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        sum+=arr[i];
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        ans+=power(2,sum-arr[i])*(power(val[i]+1,arr[i])-1);
        ans%=MOD;
    }
    cout<<(ans+MOD)%MOD<<endl;
    return 0;
}
