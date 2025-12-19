#include<bits/stdc++.h>
using namespace std;

int n,m;
char s[305];
char word[605][30];
int dp[305];

int main()
{
    cin>>n>>m;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        scanf("%s",word[i]+1);
    }
    for(int i=1;i<=m;i++){
        dp[i]=i;
        for(int j=1;j<=n;j++){
            int len=strlen(word[j]+1);
            int cnt=0;
            int u=i;
            for(u=i;u>=1;u--){
                if(word[j][len]==s[u]){
                    len--;
                }
                else{
                    cnt++;
                }
                if(len==0){
                    break;
                }
            }
            if(u!=0){
                dp[i]=min(dp[i],dp[u-1]+cnt);
            }
        }
    }
    cout<<dp[m]<<endl;
    return 0;
}