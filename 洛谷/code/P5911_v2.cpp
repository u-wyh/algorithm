#include<bits/stdc++.h>
using namespace std;

int n,limit;
struct node{
    int t,w;
    int i;
}nums[16];
int dp[1<<16][16];

int dfs(int *w,int *t,int status,int index){
    if(index==n){
        return 0;
    }
    if(status==0){
        return 0;
    }
    if(dp[status][index]){
        return dp[status][index];
    }
    if((status&(1<<index))==0){
        return dfs(w,t,status,index+1);
    }
    int ans=INT_MAX;
    for(int j=status;j>0;j=(j-1)&status){
        if((j&(1<<index))==0&&w[j]<=limit){
            ans=min(ans,t[j]+dfs(w,t,status^j,index+1));
        }
    }
    dp[status][index]=ans;
    return ans;
}

int main()
{
    cin>>limit>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].t>>nums[i].w;
        nums[i].i=i;
    }
    int w[1<<n],t[1<<n];
    for(int i=0;i<(1<<n);i++){
        w[i]=0;
        t[i]=0;
    }
    for (int i = 0, W, T, h; i < n; i++) {
        W = nums[i].w;
        T = nums[i].t;
        h = 1 << i;
        for (int j = 0; j < h; j++) {
            w[h | j] = w[j] + W;
            t[h | j] = max(t[j] , T);
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j]=0;
        }
        cout<<w[i]<<' '<<t[i]<<endl;
    }
    cout<<dfs(w,t,(1<<n)-1,0);
    return 0;
}

