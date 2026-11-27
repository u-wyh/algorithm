// https://www.luogu.com.cn/problem/P1281
// 题意：m 本书按顺序分给 k 人，每人抄连续且非空的一段，速度一样。让每个人的抄写页数中的最大值尽量小。
// 输出各人抄写的起止书号，有多解时优先让编号靠前的人少抄。
// 数据范围：1 ≤ k ≤ m ≤ 500，每本页数在 [1,10000]。
// 算法标签：二分查找、贪心、前缀和

#include<stdio.h>
#include<limits.h>

int check(int limit,int *nums,int n)
{
    int parts=1;
    int sum=0;
    for(int i=1;i<=n;i++){
        if(nums[i]>limit)
            return INT_MAX;
        if(sum+nums[i]>limit){
            parts++;
            sum=nums[i];
        }else{
            sum+=nums[i];
        }
    }
    return parts;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+1],sum[n+1];
    nums[n]=0;
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        sum[i]=sum[i-1]+nums[i];
    }
    int l=0,r=sum[n],mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,nums,n)<=k){
            ans=mid;
            r=mid-1;
        } else {
            l=mid+1;
        }
    }
    //printf("%d\n",ans);
    int i=1,sum2;
    while(k--){
        sum2=0;
        printf("%d ",i);
        while(sum2<=ans){
            //printf("%d ",sum2);
            sum2+=nums[i++];
            if(i==n+2)
                break;
        }
        i--;
        printf("%d\n",i-1);
    }
    return 0;
}
