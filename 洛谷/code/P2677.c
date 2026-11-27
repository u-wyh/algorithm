// https://www.luogu.com.cn/problem/P2677
// 题意：N 头奶牛各有身高 H_i，书架高度为 B。
// 选出若干奶牛使其身高之和 >= B，求身高之和最少比 B 高多少。
// 输出最小非负差值。
// 数据范围：1 <= N <= 20，1 <= H_i <= 10^6，1 <= B <= S。
#include<stdio.h>
// 算法标签：深度优先搜索、剪枝

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
