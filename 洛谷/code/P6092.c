// https://www.luogu.com.cn/problem/P6092
// 题意：N 天内收到 M 个任务（第 i 个任务在第 S_i 天到达，第 N-D 天后无任务），每台机器每天只能做 1 个任务，每个任务最多推迟 D 天完成
// 求完成全部任务至少需要多少台机器。
// 数据范围：1 <= N <= 10^5，0 <= D < N，1 <= M < 10^6。
// 算法标签：二分答案、贪心、排序
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int check(int limit,int *nums,int m,int n,int d){
    int sum=0;
    for(int i=1;i<=n;i++){
        if(sum>=m){
            return true;
        }
        for(int j=1;j<=limit;j++){
            if(nums[sum]<=i&&sum<m){
                if(nums[sum]+d<i){
                    return false;
                }else{
                    sum++;
                }
            }else {
                break;
            }
        }
    }
    return sum >= m;
}

int main()
{
    int n,d,m;
    scanf("%d %d %d",&n,&d,&m);
    int nums[m+1];
    for(int i=1;i<=m;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,m,sizeof(int),cmp);
    /*
    for(int i=1;i<=m;i++){
        printf("%3d",nums[i]);
    }
    printf("\n");
    */
    nums[0]=0;
    int l=0,r=m,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,m,n,d)){
            ans=mid;
            r=mid-1;
        } else {
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
