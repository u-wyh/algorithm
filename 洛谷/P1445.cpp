#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

int n;

int prime[MAXN];
int cnt;
int num[MAXN];

int t[MAXN];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!num[i]){
            prime[++cnt]=i;
            num[i]=cnt;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=j;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

signed main()
{
    cin>>n;
    prepare(n);
    // for(int i=2;i<=n;i++){
    //     int tmp=i;
    //     while(tmp!=1){
    //         t[num[tmp]]++;
    //         tmp/=prime[num[tmp]];
    //     }
    // }
    // int ans=1;
    // for(int i=1;i<=cnt;i++){
    //     ans=(ans*(2*t[i]+1))%MOD;
    // }
    int ans=1;
    for(int i=1;i<=cnt;i++){
        int count=0;
        int power=prime[i];
        while(power<=n){
            count+=n/power;
            power*=prime[i];
        }
        ans=(ans*(2*count+1))%MOD;
    }
    cout<<ans<<endl;
    return 0;
}