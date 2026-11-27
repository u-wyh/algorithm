// https://www.luogu.com.cn/problem/P8344
// 题意：T 组询问，有 x 个金色木板、y 个银色木板及容量为 z 的空容器。
// 向容器放入金色木板前容器须至少还有 1 个空位，
// 且放入金色木板后会立即丢弃容器内所有银色木板。
// 判断是否存在方案使所有 x + y 个木板都曾被放入过容器，
// 能则输出 Renko，否则输出 Merry。
// 数据范围：100% 数据满足 1 <= T <= 1000，
// 1 <= x, z <= 10^9，1 <= y <= 5*10^17。
// 算法标签：数学
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int k=1;k<=t;k++)
    {
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        if(a>c||(a*(2*c-1-a)/2+(c-a))<b)
        {
            printf("Merry\n");
        }
        else
            printf("Renko\n");
    }
    return 0;
}
