// https://www.luogu.com.cn/problem/P2983
// 题意：输入巧克力种类数 N、总预算 B，以及每种巧克力的单价 P_i 和只喜欢该种巧克力的奶牛数量 C_i（每种巧克力供应无限）。
// 每头牛只对其指定的唯一一种巧克力感到满意；在总花费不超过预算 B 的前提下购买巧克力分配给奶牛。
// 求最多能满足多少头奶牛。
// 输出一行一个整数，表示最多能满足的奶牛数量。
// 数据范围：对于 100% 的数据，1 <= N <= 100000，1 <= P_i <= 10^18，1 <= C_i <= 10^18
// 1 <= B <= 10^18。
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    long long p,c;
}chocolate;

int cmp(const void *a,const void *b){
    chocolate * ca=(chocolate *)a;
    chocolate * cb=(chocolate *)b;

    return ca->p - cb->p;
}

int main()
{
    int n;
    long long m;
    scanf("%d %lld",&n,&m);
    chocolate nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&nums[i].p,&nums[i].c);
    }
    qsort(nums+1,n,sizeof(chocolate),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(m>=nums[i].p*nums[i].c){
            m-=nums[i].p*nums[i].c;
            ans+=nums[i].c;
        }else if(m>=nums[i].p){
            ans+=m/nums[i].p;
            m=0;
        }else{
            break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
