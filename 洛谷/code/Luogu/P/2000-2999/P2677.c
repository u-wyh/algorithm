#include<stdio.h>

int n,m;
int nums[21];
int ans=1e6;

int min(int a,int b){
    return a<b?a:b;
}

void dfs(int u,int v){
    if(v>ans)
        return ;
    if(u>n&&v>=m){
        ans=min(ans,v);
        return ;
    }
    else if(u>n)
        return ;
    dfs(u+1,v);
    v+=nums[u];
    dfs(u+1,v);
    v-=nums[u];
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    dfs(1,0);
    printf("%d\n",ans-m);
    return 0;
}
