// https://www.luogu.com.cn/problem/P5963
// 题意：给定 N 张双面写有整数 a_i, b_i 的卡牌，
// 将所有卡牌按任意顺序（可翻转）填入「□-□+□-□+...-□」格式表达式
// （即共 N 项
// 奇数位为正、偶数位为负，首尾符号均为 -），求表达式能得到的最小值。
// 数据范围：2 <= N <= 10^5（N 为偶数），
// |a_i|, |b_i| <= 2000。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}num;

int cmp(const void *a,const void *b)
{
    num * na=(num *)a;
    num * nb=(num *)b;

    return ((na->a+na->b)-(nb->a+nb->b));
}

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    num nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(num),cmp);
    long long  ans=0;
    for(int i=1;i<=n/2;i++){
        ans+=min(nums[i].a,nums[i].b);
    }
    for(int i=n/2+1;i<=n;i++){
        ans-=max(nums[i].a,nums[i].b);
    }
    printf("%lld\n",ans);
    return 0;
}
