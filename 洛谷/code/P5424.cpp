#include<bits/stdc++.h>
using namespace std;
const int MAXN = 405;

int dp[MAXN][MAXN];//表示从i到j最少的剩余空间
int f[MAXN][MAXN];//表示从i到j只用一个框的剩余空间
int sum[MAXN];
int arr[MAXN];
int n,m;
int tree[MAXN<<2];

void build(int l,int r,int i){
    if(l==r){
        tree[i]=arr[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
    //cout<<i<<": "<<l<<' '<<r<<' '<<tree[i]<<endl;
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=0;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum[i]=sum[i-1]+arr[i];
        //cout<<sum[i]<<' ';
    }
    //cout<<endl;
    build(1,n,1);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            f[i][j]=-sum[j]+sum[i-1]+(j-i+1)*query(i,j,1,n,1);
            //cout<<f[i][j]<<' ';
        }
        //cout<<endl;
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=f[1][i];
    }
    for(int i=1;i<=m;i++){
        dp[i+1][i]=0;
    }
    for(int j=1;j<=m;j++){
        for(int i=j+2;i<=n;i++){
            dp[i][j]=INT_MAX;
            for(int k=1;k<=i-1;k++){
                dp[i][j]=min(dp[i][j],dp[k][j-1]+f[k+1][i]);
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}
