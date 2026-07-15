#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int op,n;
double dp[MAXN][MAXN];

double solve1(){
    double result=0;
    for(int i=2;i<=n;i++){
        result+=2.0/i;
    }
    return result;
}

double solve2(){
    if(n==1){
        return 0;
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            double sum=0;
            for(int k=1;k<i;k++){
                sum+=dp[k][j-1]+dp[i-k][j-1]-dp[k][j-1]*dp[i-k][j-1];
            }
            dp[i][j]+=sum/(i-1);
        }
    }
    double res=0;
    for(int j=1;j<n;j++){
        res+=dp[n][j];
    }
    return res;
}

int main()
{
    cin>>op>>n;
    double ans;
    if(op==1){
        ans=solve1();
    }
    else{
        ans=solve2();
    }
    printf("%.6lf\n",ans);
    return 0;
}