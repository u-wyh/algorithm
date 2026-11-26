// https://www.luogu.com.cn/problem/P1288
// 题意：环上每条边有计数，硬币从首尾两条边相接的点出发。
// 两人轮流选硬币相邻的一条非零边，把计数减小到任意非负数，并把硬币移到边的另一端。
// 不能行动者输，先手能赢输出 YES，否则输出 NO。
// 数据范围：N ≤ 20，边上数值在 [0,30]，至少有一条边的初始值为 0。

#include<stdio.h>

int main()
{
    int n,cnt=0;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    int k1,k2;
    for(int i=1;i<=n;i++){
        if(nums[i]==0){
            k1=i;
            break;
        }
    }
    for(int i=n;i>=1;i--){
        if(nums[i]==0){
            k2=(n-i+1);
            break;
        }
    }
    if(k1%2==1&&k2%2==1){
        printf("NO\n");
    }else{
        printf("YES\n");
    }
    return 0;
}

