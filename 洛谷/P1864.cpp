#include<bits/stdc++.h>
using namespace std;
const int MAXN = 75;
const long long INF = 1e15;

int n,K;
struct node{
    int key,weight,freq;
};
node nums[MAXN];
int val[MAXN];
int sum[MAXN];

long long dp[MAXN][MAXN][MAXN];

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

bool cmp(node a,node b){
    return a.key<b.key;
}

int find(int v){
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(val[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read(),K=read();
    for(int i=1;i<=n;i++){
        nums[i].key=read();
    }
    for(int i=1;i<=n;i++){
        nums[i].weight=read();
        val[i]=nums[i].weight;
    }
    for(int i=1;i<=n;i++){
        nums[i].freq=read();
    }
    sort(val+1,val+n+1);
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+nums[i].freq;
        nums[i].weight=find(nums[i].weight);
    }
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                dp[i][j][k]=INF;
            }
        }
    }
    for(int i=1;i<=n+1;i++){
        for(int k=1;k<=n;k++){
            dp[i][i-1][k]=0;
        }
    }
    for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=1;k<=n;k++){
                for(int t=i;t<=j;t++){
                    long long cost=sum[j]-sum[i-1];

                    if(nums[t].weight>=k){
                        dp[i][j][k]=min(dp[i][j][k],dp[i][t-1][nums[t].weight]+dp[t+1][j][nums[t].weight]+cost);
                    }
                    dp[i][j][k]=min(dp[i][j][k],dp[i][t-1][k]+dp[t+1][j][k]+cost+K);
                }
            }
        }
    }
    cout<<dp[1][n][1]<<endl;
    return 0;
}