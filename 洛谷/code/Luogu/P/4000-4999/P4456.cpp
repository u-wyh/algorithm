#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+1;
const int MAXM = 1e7+2;

int n,a,b,m;
int nums1[MAXN];
int nums2[MAXN];
int inv[MAXM];
long long f[MAXN];

inline int power(int a,int b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%m;
        }
        a=(1ll*a*a)%m;
        b>>=1;
    }
    return (int)ans;
}

void build(){
    for(int i=0;i<=(n+1)/2;i++){
        nums1[i]=power(i,b);
        nums2[i]=power(n-i,a);
    }
    inv[1]=1;
    for(int i=2;i<=n+1;i++){
        inv[i]=(int)(m-1ll*inv[m%i]*(m/i)%m+m)%m;
    }
}

int main()
{
    cin>>n>>a>>b>>m;
    build();
    f[0]=1;
    for(int i=1;i<=(n+1)/2;i++){
        f[i]=(f[i-1]*(n-2*i+3)%m*(n-2*i+2)%m*inv[i]%m*inv[n-i+2]%m+m)%m;
    }
    long long ans=0;
    for(int i=0;i<=(n+1)/2;i++){
        ans+=f[i]*nums1[i]%m*nums2[i]%m;
        ans%=m;
    }
    cout<<ans<<endl;
    return 0;
}