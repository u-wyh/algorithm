#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 1e9+7;

int n,m;
int inv;

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

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    inv=power(25,MOD-2);
    while(T--){
        cin>>n;
        m=(n+1)/2;
        int ans=(((2*m-1)%MOD*power(26,m+1)%MOD-26-2*(power(26,m+1)-26*26)%MOD*inv%MOD)%MOD*inv%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}