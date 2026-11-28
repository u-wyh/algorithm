// https://www.luogu.com.cn/problem/P10483
// 题意：有 N 只小猫，第 i 只重 C[i]。
// 一辆缆车上的总重量不能超过 W，把所有猫都运下山最少需要几辆缆车。
// 数据范围：1 ≤ N ≤ 18，1 ≤ C[i],W ≤ 10^8。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索、剪枝

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
