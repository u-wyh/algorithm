#include<bits/stdc++.h>
using namespace std;

int n,l,r;
int nums[45],ans=0,lastsum[45];

void dfs(int x,int y){
    if(y>r||y+lastsum[x]<l)
        return ;
    if(x>n){
        ans++;
        return ;
    }
    dfs(x+1,y);
    dfs(x+1,y+nums[x]);
}

int main()
{
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=n;i>=1;i--){
        lastsum[i]=lastsum[i+1]+nums[i];
    }
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}
