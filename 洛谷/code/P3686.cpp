#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 3e5+5;
const int INF = 1e15;

int n,d,m,n1,n2;
unordered_map<int,int>cost;
int nums[MAXN];
int dp[MAXN];//表示到达第i个城市的最小代价

inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

signed main()
{
    n=read(),d=read();
    n1=n+1,n2=(n+1)*(n+1);
    for(int i=1;i<=d;i++){
        nums[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        char op;
        u=read(),v=read();
        cin>>op;
        w=read();
        int k=(op=='R')?1:0;
        k=k*n2+u*n1+v;
        int tmp=cost[k];
        if(tmp==0){
            cost[k]=w;
        }
        else{
            cost[k]=min(w,tmp);
        }

        if(op=='R'){
            k=v*n1+u;
            tmp=cost[k];
            if(tmp==0){
                cost[k]=w;
            }
            else{
                cost[k]=min(w,tmp);
            }
        }
        // cout<<' '<<k<<' '<<cost[k]<<endl;
    }

    dp[1]=0;
    for(int i=2;i<=d;i++){
        dp[i]=INF;

        int u=nums[i-1],v=nums[i];
        int c1=cost[u*n1+v];
        int c2=cost[n2+u*n1+v];
        if(c1||c2){
            if(c1==0){
                dp[i]=min(dp[i],dp[i-1]+c2);
            }
            else if(c2==0){
                dp[i]=min(dp[i],dp[i-1]+c1);
            }
            else{
                dp[i]=min(dp[i],dp[i-1]+min(c1,c2));
            }
        }

        if(nums[i-2]!=v){
            continue;
        }
        c2=cost[n2+v*n1+u];
        if(c2==0){
            continue;
        }
        dp[i]=min(dp[i],dp[i-2]+c2);
    }
    cout<<dp[d]<<endl;
    return 0;
}