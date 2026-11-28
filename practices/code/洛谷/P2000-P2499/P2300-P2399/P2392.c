// https://www.luogu.com.cn/problem/P2392
// 题意：4 科分别有 s_1..s_4 道题，给出每题耗时，必须按科复习。
// 每科内可同时做至多 2 道不同的题，求完成所有 4 科的最短时间。
// 输出最短总时间。
// 数据范围：1 <= s_1, s_2, s_3, s_4 <= 20，
// 每题耗时 in [1, 60]。
// 难度评分：1000（洛谷分级换算）
// 算法标签：深度优先搜索、回溯、剪枝
#include<stdio.h>

int s[4],a[21],nowtime,maxtime,sum,ans,maxdeep;

int max(int a,int b){
    return a>b?a:b;
}

void dfs(int x){
    if(x>maxdeep){
        maxtime=max(maxtime,nowtime);
        return ;
    }
    if(nowtime+a[x]<=sum/2){
        nowtime+=a[x];
        dfs(x+1);
        nowtime-=a[x];
    }
    dfs(x+1);
}

int main()
{
    for(int i=0;i<4;i++){
        scanf("%d",&s[i]);
    }
    for(int i=0;i<4;i++){
        nowtime=0;
        maxdeep=s[i];
        sum=0;
        for(int j=1;j<=s[i];j++){
            scanf("%d",&a[j]);
            sum+=a[j];
        }
        maxtime=0;
        dfs(1);
        ans+=(sum-maxtime);
    }
    printf("%d\n",ans);
    return 0;
}
