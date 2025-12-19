#include<bits/stdc++.h>
using namespace std;
#define int long long

int m,n;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%m;
        }
        a=(a*a)%m;
        b>>=1;
    }
    return ans;
}

int euler(int n){
    int tmp=n;
    int temp=1;
    for(int i=2;i*i<=tmp;i++){
        if(tmp%i){
            continue;
        }
        temp*=(i-1);
        tmp/=i;
        while(tmp%i==0){
            temp*=i;
            tmp/=i;
        }
    }
    if(tmp>1){
        temp*=(tmp-1);
    }
    return temp;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int prime[100005];
int tot;
int cnt[100005];

signed main()
{
    cin>>m>>n;
    if(gcd(n,m)!=1){
        cout<<"Let's go Blue Jays!";
        return 0;
    }
    int ans=euler(m);
    int val=ans;
    // cout<<ans<<endl;
    for(int i=2;i*i<=ans;i++){
        if(ans%i){
            continue;
        }
        prime[++tot]=i;
        while((ans%i)==0){
            cnt[tot]++;
            ans/=i;
        }
    }
    if (ans > 1) {  // 处理剩余的质因数
        prime[++tot] = ans;
        cnt[tot] = 1;
    }
    for(int i=1;i<=tot;i++){
        for(int j=1;j<=cnt[i];j++){
            if(power(n,val/prime[i])==1){
                val/=prime[i];
            }
            else{
                break;
            }
        }
    }
    cout<<val<<endl;
    return 0;
}