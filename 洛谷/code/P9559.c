// https://www.luogu.com.cn/problem/P9559
// 题意：多组数据（共 T 组）。
// 队伍共 n 人，第 i 人速度 v_i、体重 w_i。
// 每人可独立行动或背起至多一人（被背者不能再背人）。
// 若 i 背 j 且 w_i >= w_j 则 i 速度仍为 v_i，否则变为 v_i - (w_j - w_i)（不能变为负数）。
// 队伍速度为所有未被背负队员的最小速度，求能达到的最大队伍速度。
// 题意：第一行输入 T，每组输入 n 及 n 行 (v_i, w_i)；每组输出一行一个整数。
// 数据范围：1 <= n <= 10^5，sum(n) <= 10^5，1 <= v_i, w_i <= 10^9（未显式写 T 的上界
// 受 sum(n) <= 10^5 限制）。
// 算法标签：二分答案、贪心
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define Max 100000+5

typedef struct
{
    int v,w;
}people;

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

bool check(int limit,people *nums,int n){
    int a[Max],b[Max],m=0,k=0;
    for(int i=1;i<=n;i++){
        if(nums[i].v>limit){
            a[m++]=(nums[i].v+nums[i].w-limit);
        }else if(nums[i].v<limit){
            b[k++]=nums[i].w;
        }
    }
    if(m<k){
        return false;
    }
    qsort(a,m,sizeof(int),cmp);
    qsort(b,k,sizeof(int),cmp);
    int i=0,j=0;
    while (i < k && j < m) {
        if (a[j] < b[i]) return false;  // 如果背负者的速度小于被背负者的体重，则无法背负
        i++;
        j++;
    }
    return true;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n,max=0,min=1e9;
        scanf("%d",&n);
        people nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d %d",&nums[i].v,&nums[i].w);
            max=max>nums[i].v?max:nums[i].v;
            min=min<nums[i].v?min:nums[i].v;
        }
        int l=min,r=max,mid,ans=min;
        while(l<=r){
            mid=(l+r)/2;
            if(check(mid,nums,n)){
                ans=mid;
                l=mid+1;
            }else {
                r=mid-1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
