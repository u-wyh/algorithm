#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m;
char s[MAXN];
int sum[MAXN],dp[MAXN];
int q[MAXN],head,tail;

int main()
{
    cin>>n>>m;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='H'){
            sum[i]=1+sum[i-1];
        }
        else{
            sum[i]=sum[i-1]-1;
        }
        //cout<<sum[i]<<' ';
    }
    q[tail++]=0;
    for(int i=1;i<=n;i++){
        while(head<tail&&i-q[head]>m){
            head++;
        }
        dp[i]=dp[q[head]]+(sum[i]<=sum[q[head]]);
        while(head<tail&&(dp[i]<dp[q[tail-1]])||(dp[i]==dp[q[tail-1]]&&sum[q[tail-1]]>sum[i])){
            tail--;
        }
        q[tail++]=i;
    }
    cout<<dp[n]<<endl;
    return 0;
}
