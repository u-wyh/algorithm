#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,maxx=0;
int h[105];
int tmp[105];
int dp[105][1005];



int main()
{
    cin>>n;
    int k=INT_MAX;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        k=min(h[i],k);
        maxx=max(maxx,h[i]);
    }
    if(n%2==0){
        k=0;
    }
    for(int i=0;i<=k;i++){
        for(int j=0;j<n;j++){
            for(int p=0;p<=maxx;p++){
                dp[j][p]=0;
            }
        }
        for(int j=1;j<=n;j++){
            tmp[j]=h[j]-i;
        }
        dp[1][tmp[1]]=1;
        
    }
    return 0;
}