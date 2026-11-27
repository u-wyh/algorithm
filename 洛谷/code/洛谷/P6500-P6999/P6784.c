// https://www.luogu.com.cn/problem/P6784
// 题意：初始有 a 个 A 材料、b 个 B 材料和 c
// 块钱（每块钱可买 1 个 A 或 1 个 B），
// 建造第 i 层楼需要 i 个 A 和 i 个 B
// 求最多能建造多少层楼。
// 数据范围：0 <= a, b, c <= 10^12。
// 算法标签：贪心、枚举
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
    long long a,b,c,k=0;
    scanf("%lld %lld %lld",&a,&b,&c);
    if((a-b)<=c&&(b-a)<=c)
        k=(a+b+c)/2;
    else
        k=(c+(a<b?a:b));
    //printf("%lld\n",k);
    int ans;
    for(int i=sqrt(2*k);i>=0;i--)
    {
        printf("%d\n",i);
        if((i*(i+1)<=k*2)&&(i*(i+1)>k*2))
        {
            ans=i;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
