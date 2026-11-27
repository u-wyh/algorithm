// https://www.luogu.com.cn/problem/P1542
// 题意：按固定路线顺序往 n 个地点送包裹，出发时刻为 0。
// 第 i 个地点签收时间段为 [x_i, y_i]，距前一地点距离为 s_i。
// 早到需等待至 x_i，不能晚于 y_i，签收瞬间完成。
// 求能全部送达的前提下，车的最大速度的最小值，保留 2 位小数。
// 数据范围：
// 0 < n <= 2*10^5（地点数）
// 0 < x_i <= y_i <= 10^8（签收时间段，且 x_i 递增）
// 0 < s_i <= 10^7（路段距离，以上均为正整数）
// 算法标签：二分答案、模拟
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
    int a,b,s;
}press;

bool check(double x,press *nums,int n){
    double t=0;
    for(int i=1;i<=n;i++){
        t+=1.0*nums[i].s/x;
        if(t>nums[i].b)
            return false;
        t=t>nums[i].a?t:nums[i].a;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d",&n);
    press nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&nums[i].a,&nums[i].b,&nums[i].s);
    }
    double l=0,r=1e8,mid,ans=1e8;
    while(r-l>1e-6){
        mid=(l+r)/2;
        if(check(mid,nums,n)){
            r=mid;
            ans=mid;
        }else{
            l=mid;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
