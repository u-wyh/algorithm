// https://www.luogu.com.cn/problem/P10505
// 题意：有 n 场考试，第 i 场共 b[i] 题，答对 a[i] 题。
// 删去恰好 k 场，使剩下的答对总数除以总题数最大。
// 输出该比值乘 100 并四舍五入后的整数。
// 数据范围：1 ≤ n ≤ 1000，0 ≤ k < n，
// 0 ≤ a[i] ≤ b[i] ≤ 10^9，输入 0 0 结束。
// 难度评分：1300（洛谷分级换算）
// 算法标签：分数规划、二分答案、贪心

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
    long long  a,b,c;

}score;

int cmp(const void *a,const void *b){
    score * sa=(score *)a;
    score * sb=(score *)b;

    return sb->c - sa->c;
}

bool check(double x,score *nums,int n,int k)
{
    for(int i=1;i<=n;i++){
        nums[i].c=(100*nums[i].a-x*nums[i].b);
    }
    qsort(nums+1,n,sizeof(score),cmp);
    long long ans=0;
    for(int i=1;i<=(n-k);i++){
        ans+=nums[i].c;
        if(ans<0)
            return false;
    }
    return ans>0;
}

int main()
{
    int n,k;
    while(scanf("%d %d",&n,&k)==2&&(n+k)!=0){
        double l=0,r=1,mid,ans=0;
        score nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%lld",&nums[i].a);
        }
        for(int i=1;i<=n;i++){
            scanf("%lld",&nums[i].b);
        }
        while(r-l>1e-6){
            mid=(l+r)/2;
            if(check(mid*100,nums,n,k)){
                ans=mid;
                l=mid;
            }else{
                r=mid;
            }
        }
        printf("%.0lf\n",ans*100);
    }
    return 0;
}
