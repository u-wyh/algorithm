#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,m,k;
int arr[MAXN];
int dp[MAXN];

void compute(){
    int u=1;
    while(dp[u]<k){
        u++;
    }
    int maxlen=k;
    int last=INT_MIN;
    for(int i=1;i<=k;i++){
        while(dp[u]<k-i+1||arr[u]<=last){
            u++;
        }
        cout<<arr[u]<<' ';
        last=arr[u];
        u++;
    }
    cout<<endl;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int maxlen=0;
    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            if(arr[i]<arr[j]){
                dp[i]=max(dp[i],dp[j]);
            }
        }
        dp[i]+=1;
        maxlen=max(maxlen,dp[i]);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>k;
        if(k>maxlen){
            cout<<"Impossible"<<endl;
        }
        else{
            compute();
        }
    }
    return 0;
}
