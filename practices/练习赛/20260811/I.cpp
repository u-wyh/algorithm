#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1500;

int n;
int cnt;
int d[MAXN];
int dp[MAXN];
map<int,int>mp;

int compute(){
    if(mp[n]){
        return mp[n];
    }

    cnt=0;
    for(int i=1;i*i<n;i++){
        if(n%i==0){
            d[++cnt]=i;
            d[++cnt]=n/i;
        }
    }
    int v=sqrt(n);
    if(v*v==n){
        d[++cnt]=v;
    }

    if(cnt==2){
        return n-1;
    }
    sort(d+1,d+cnt+1);
    
    for(int i=1;i<=cnt;i++){
        dp[i]=n;
    }
    dp[1]=0;
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<i;j++){
            dp[i]=min(dp[i],dp[j]+(d[i]-1)/d[j]);
        }
    }
    return dp[cnt];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        n++;
        mp[n]=compute();
        cout<<mp[n]<<endl;
    }
    return 0;
}