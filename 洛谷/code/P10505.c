// https://www.luogu.com.cn/problem/P10505
// 题意：有 n 场考试，第 i 场共 b[i] 题，答对 a[i] 题。删去恰好 k 场，使剩下的答对总数除以总题数最大。
// 输出该比值乘 100 并四舍五入后的整数。
// 数据范围：1 ≤ n ≤ 1000，0 ≤ k < n，0 ≤ a[i] ≤ b[i] ≤ 10^9，输入 0 0 结束。
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

bool check(int x,score *nums,int n,int k)
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
        long long  l=0,r=0,mid,ans=0;
        score nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%lld",&nums[i].a);
        }
        for(int i=1;i<=n;i++){
            scanf("%lld",&nums[i].b);
            r=r>(100*nums[i].a/nums[i].b)?r:(100*nums[i].a/nums[i].b);
        }
        r+=1;
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(mid,nums,n,k)){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
