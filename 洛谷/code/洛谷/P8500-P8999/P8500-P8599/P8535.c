// https://www.luogu.com.cn/problem/P8535
// 题意：汉字数字 0..9
// （题图与点阵给出顺序为一、二、三、四、五、六、七、八、九、〇）
// 分别由 5, 8, 15, 30, 23, 11, 17, 10
// 18, 24 个 * 组成。
// 输入可用的 * 数量上限 n，
// 求用不超过 n 个 * 能拼出的最大汉字数字对应的整数
// （直接按位拼接数字，不考虑千百等单位）。
// 数据范围：100% 数据满足 5 <= n <= 10^6。
// 算法标签：贪心、数学
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a=n%5;
    int b=n/5;
    if(a>=3)
    {
        printf("2");
        for(int i=1;i<b;i++)
            printf("1");
    }
    else
    {
        for(int i=1;i<=b;i++)
            printf("1");
    }
    return 0;
}
