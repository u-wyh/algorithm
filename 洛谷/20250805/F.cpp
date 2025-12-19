#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e5+5;

int n;
int nums[MAXN];
int a,b;

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

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        if(nums[i]%2){
            a++;
        }
        else{
            b++;
        }
    }
    int ans=(a*b)%MOD;
    cout<<ans<<endl;
    return 0;
}