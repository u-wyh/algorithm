#include<bits/stdc++.h>
using namespace std;

int n,ans=n,now=1;
int nums[55],vis[55];

void dfs(int x,int flag,int temp){
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=vis[i];
    }
    if(sum==n){
        ans=min(ans,now);
    }
    if(flag==0){
        now++;
        vis[x+1]=1;
        dfs(x+1,0,nums[x+1]);
        vis[x+1]=0;
        now--;
        if(nums[x+1]>nums[x]){
            vis[x+1]=1;
            dfs(x+1,1,nums[x+1]);
            vis[x+1]=0;
        }else if(nums[x+1]<nums[x]){
            vis[x+1]=1;
            dfs(x+1,-1,nums[x+1]);
            vis[x+1]=0;
        }else{
            now++;
            vis[x+1]=1;
            dfs(x+1,0,nums[x+1]);
            vis[x+1]=0;
            now--;
        }
    }else if(flag==1){

    }

}

int main()
{
    while(scanf("%d",&n)==1&&n!=0){
        ans=n;
        memset(nums,-1,sizeof(nums));
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i]);
        }
        vis[1]=1;
        dfs(1,0,nums[1]);
    }
    return 0;
}
