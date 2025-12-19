#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int prime[MAXN];
int cnt;
bool vis[MAXN];

int ans[10];
int len;

void euler(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

bool isprime(int val){
    for(int i=2;i*i<=val;i++){
        if(val%i==0){
            return false;
        }
    }
    return true;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

signed main()
{
    euler(100000);
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        int maxnum=gcd(a,b);
        int tmp=maxnum;
        if(maxnum==1||isprime(maxnum)){
            cout<<-1<<endl;
            continue;
        }
        // cout<<' '<<maxnum<<endl;
        len=0;
        int t=0;
        for(int i=1;i<=cnt&&t<=2;i++){
            if(maxnum%prime[i]==0){
                t++;
                maxnum/=prime[i];
                ans[++len]=prime[i];
                if(maxnum%prime[i]==0){
                    ans[++len]=prime[i]*prime[i];
                }
            }
        }
        for(int i=1;i<=cnt;i++){
            while(maxnum%prime[i]==0){
                maxnum/=prime[i];
            }
        }
        if(maxnum!=1&&isprime(maxnum)){
            ans[++len]=maxnum;
        }
        sort(ans+1,ans+len+1);
        cout<<(tmp/ans[2])<<endl;
    }
    return 0;
}