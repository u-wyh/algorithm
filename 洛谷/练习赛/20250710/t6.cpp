#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int nums[MAXN];
int dp[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        for(int i=1;i<=n-2;i++){
            dp[i][i+2]=min(max(nums[i],nums[i+1]),max(nums[i+1],nums[i+2]));
        }
        for(int len=5;len<=n;len+=2){
            for(int l=1;l+len-1<=n;l++){
                int r=l+len-1;
                dp[l][r]=max(max(min(max(nums[l],nums[l+1]),max(nums[l+1],dp[l+2][r])),min(max(dp[l][r-2],nums[r-1]),max(nums[r-1],nums[r]))),min(max(nums[l],dp[l+1][r-1]),max(dp[l+1][r-1],nums[r])));
            }
        }
        cout<<dp[1][n]<<endl;
    }
    return 0;
}