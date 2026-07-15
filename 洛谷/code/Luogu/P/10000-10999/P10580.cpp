#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 4e4+5;

bool vis[MAXN];
int prime[MAXN];
int cnt;

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

void euler(int n){
    for(int i=2;i<=n;i++){
        if(vis[i]==0){
            prime[++cnt]=i;
        }

        //无论是不是质数  都要进行下面的过程
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                //如果i可以整除prime[j]说明一定含有这个质因子
                //那么如果继续的话  就是将接下来的数字的按照下一个质数作为他的最小质因子排除的
                //而不是被最小质因子排除的  所以不能继续  要立即跳出
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
}

signed main()
{
    euler(40000);
    int T;
    cin>>T;
    while(T--){
        int x,y,n;
        cin>>x>>y>>n;
        y/=x;
        x=y;
        int ans=1;
        for(int i=1;i<=cnt&&x!=1;i++){
            int cnt=0;
            while(x%prime[i]==0){
                cnt++;
                x/=prime[i];
            }
            // cout<<' '<<prime[i]<<' '<<cnt<<' '<<x<<endl;
            if(cnt)
                ans=ans*((power(cnt+1,n)%MOD-2*power(cnt,n)%MOD+power(cnt-1,n)%MOD+MOD)%MOD+MOD)%MOD;
        }
        if(x>1){
            ans=(ans*(power(2,n)-2)%MOD+MOD)%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}