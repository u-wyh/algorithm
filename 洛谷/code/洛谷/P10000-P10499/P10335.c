// https://www.luogu.com.cn/problem/P10335
// 题意：A、B 轮流操作，A 先手。
// 每次可以合并任意两个数为它们的和，
// 也可以取走一个数并把其余数的和给对方、立即结束。
// 得数较大者胜，判断 A 是否有必胜策略，输出 YES 或 NO。
// 数据范围：1 ≤ T ≤ 10^5，1 ≤ n ≤ 5 × 10^5，
// 所有 n 之和不超过 10^6，1 ≤ a[i] ≤ 10^9，
// 每组的数之和为奇数。
// 算法标签：数学、分类讨论

#include <stdio.h>
#include <stdlib.h>

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1],maxans=0;
        long long sum=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i]);
            maxans=max(maxans,nums[i]);
            sum+=nums[i];
        }
        if(maxans<=sum/2&&n%2==1){
            printf("NO\n");
        }else{
            printf("YES\n");
        }
    }
    return 0;
}
