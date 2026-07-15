#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m,K;
long dp[100][1<<6][1<<6][22];//dp[i][s][ss][k]到了第i行，上一行状态是s上上一行是ss已经填了k个
int cnt[1<<6];

long f(int i,int s,int ss,int k){
    //cout<<' '<<i<<endl;
    if(k>K){
        return 0;
    }
    if(i==n){
        if(k==K)
            return 1;
        else
            return 0;
    }
    if(dp[i][s][ss][k]!=-1){
        return dp[i][s][ss][k];
    }
    long ans=0;
    for(int now=0;now<(1<<m);now++){
        if((((ss<<1)|(ss>>1)|(s<<2)|(s>>2))&now)==0){
            ans=(ans+f(i+1,now,s,k+cnt[now]))%MOD;
        }
    }
    dp[i][s][ss][k]=ans;
    return ans;
}

int main()
{
    cin>>n>>m>>K;
    if(m>n){
        n^=m;
        m^=n;
        n^=m;
    }
    //cout<<n<<' '<<m<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<m);j++){
            for(int u=0;u<(1<<m);u++){
                for(int v=0;v<=K;v++){
                    dp[i][j][u][v]=-1;
                }
            }
        }
    }
    cnt[0]=0;
    for(int i=1;i<(1<<m);i++){
        int s=i&-i;
        cnt[i]=cnt[i^s]+1;
        //cout<<i<<' '<<cnt[i]<<endl;
    }
    //cout<<n<<' '<<m<<endl;
    cout<<f(0,0,0,0)<<endl;
    return 0;
}
