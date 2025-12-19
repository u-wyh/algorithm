#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = 1e6+5;

int n;
int nums[MAXN];
int lst[MAXM];
int dp[MAXN];

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

signed main()
{
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
            lst[nums[i]]=0;
            dp[i]=0;
        }
        for(int i=1;i<=n;i++){
            if(lst[nums[i]]!=0){
                dp[i]+=max(dp[lst[nums[i]]],dp[lst[nums[i]]+1])+nums[i];
                for(int j=lst[nums[i]]+2;j<i;j++){
                    if(nums[j]==nums[j-1])
                        dp[i]+=nums[j];
                }
            }
            lst[nums[i]]=i;
            dp[i]=max(dp[i],dp[i-1]);
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}