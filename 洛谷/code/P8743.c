// https://www.luogu.com.cn/problem/P8743
// 题意：T 组独立询问，每组给定长度为 n_i 的数列 X_1..X_{n_i}；
// 初始 Alice 和 Bob 分别有整数 a=0, b=0，Alice 先手轮流操作，每步选一个未用过的 X_k 异或到 a 或 b 上
// 所有数用完后数值大者胜（相同为平局）；
// 双方最优策略下输出每组结果（1 表示 Alice 胜，0 表示平局，-1 表示 Alice 败）。
// 数据范围：1 <= T <= 2*10^5，1 <= sum(n_i) <= 2*10^5，0 <= X_i < 2^20。
#include<stdio.h>
#include<string.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1],cnt[21],eor=0;
        for(int j=0;j<=20;j++){
            cnt[j]=0;
        }
        for(int j=1;j<=n;j++){
            scanf("%d",&nums[j]);
            eor^=nums[j];
            for(int k=0;k<=20;k++){
                cnt[k]+=((nums[j]>>k)&1);
            }
        }
        if(eor==0){
            printf("0\n");
        }else{
            for(int k=20;k>=0;k--){
                if(cnt[k]%2==0)
                    continue;
                if(cnt[k]==1){
                    printf("1\n");
                }else if((n-cnt[k])&1){
                    printf("-1\n");
                }else{
                    printf("1\n");
                }
                break;
            }
        }
    }
    return 0;
}
