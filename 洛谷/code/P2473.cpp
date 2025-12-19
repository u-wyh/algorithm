#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 1<<16;

int k,n;
int sta[20];
int val[20];
double dp[MAXN][MAXM];

int main()
{
    cin>>k>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        int x;
        while(cin>>x&&x){
            sta[i]|=(1<<(x-1));
        }
    }
    int status=1<<n;
    for(int i=1;i<=k;i++){
        for(int j=0;j<status;j++){
            for(int p=1;p<=n;p++){
                if((sta[p]&j)==sta[p]){
                    dp[i][j]+=max(dp[i-1][j],dp[i-1][j|(1<<(p-1))]+val[p])/n;
                }
                else{
                    dp[i][j]+=dp[i-1][j]/n;
                }
            }
        }
    }
    printf("%.6lf",dp[k][0]);
    return 0;
}