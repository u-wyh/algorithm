#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int q[MAXN];
int dp[MAXN];
int n;
int arr[MAXN];
int m;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int k;
        cin>>k;
        int head=1,tail=2;
        q[head]=1;
        dp[1]=0;
        for(int i=2;i<=n;i++){
            while(head<tail&&q[head]+k<i){
                head++;
            }
            if(arr[i]<arr[q[head]]){
                dp[i]=dp[q[head]];
            }
            else{
                dp[i]=dp[q[head]]+1;
            }
            while(head<tail&&(dp[q[tail-1]]>dp[i]||(dp[q[tail-1]]==dp[i]&&arr[q[tail-1]]<=arr[i]))){
                tail--;
            }
            q[tail]=i;
            tail++;
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
