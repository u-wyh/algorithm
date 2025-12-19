#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10;
const int INF = 1e9;

int p[]={0,50,10,3,12,5,50,6};
int dp[MAXN][MAXN];
int ans[MAXN][MAXN];

void traceback(int l,int r){
    if(l==r){
        cout<<char('A'+l-1);
        return ;
    }
    cout<<"(";
    int split=ans[l][r];
    traceback(l,split-1);
    traceback(split,r);
    cout<<")";
}

int main()
{
    for(int i=1;i<=6;i++){
        dp[i][i]=0;
        for(int j=i+1;j<=6;j++){
            dp[i][j]=INF;
        }
    }
    for(int len=2;len<=6;len++){
        for(int i=1,j=i+len-1;j<=6;i++,j++){
            for(int k=i+1;k<=j;k++){
                int res=dp[i][k-1]+dp[k][j]+p[i]*p[k]*p[j+1];
                if(dp[i][j]>res){
                    dp[i][j]=res;
                    ans[i][j]=k;
                }
            }
        }
    }
    traceback(1,6);
    cout<<endl;
    cout<<dp[1][6]<<endl;
    return 0;
}