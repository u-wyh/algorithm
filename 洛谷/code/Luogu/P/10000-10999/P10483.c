#include<stdio.h>
#include<stdlib.h>

#define MAX 19

int n,m;
int nums[MAX],sum[MAX],ans;

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int min(int a,int b){
    return a<b?a:b;
}

void dfs(int u,int v){
    if(v>=ans){
        return ;
    }
    if(u==n){
        ans=min(ans,v);
        return ;
    }
    for(int i=0;i<v;i++){
		if(sum[i]+nums[u]<=m){
			sum[i]+=nums[u];
			dfs(u+1,v);
			sum[i]-=nums[u];
		}
	}
	sum[v]=nums[u];
	dfs(u+1,v+1);
	sum[v]=0;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    ans=n;
    qsort(nums,n,sizeof(int),cmp);
    dfs(0,0);
    printf("%d\n",ans);
    return 0;
}
