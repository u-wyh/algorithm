// https://www.luogu.com.cn/problem/P3742
// 题意：输入字符串长度 n，以及两个长度为 n 的小写字母串 x 和 y。
// 定义 f(s1, s2)
// 为逐位取较小字符得到的新串（g_i = min(s1_i, s2_i)）
// 求任意一个满足 f(x, z) = y 的小写字母串 z。
// 输出满足条件的字符串 z，若无解则输出 -1。
// 数据范围：1 <= n <= 100。
// 难度评分：800（洛谷分级换算）
// 算法标签：贪心、字符串
#include<stdio.h>
#include<string.h>

int main()
{
    int n;
    scanf("%d", &n);
    char s1[n+1], s2[n+1], s3[n+1];  // 加1以存储字符串结束符'\0'
    scanf("%s", s1);
    scanf("%s", s2);

    int lessThan = 0;  // 用于标记是否发现s1中有字符小于s2中的对应字符

    for(int i = 0; i < n; i++)  // 正确的循环边界
    {
        if(s1[i] < s2[i])
        {
            printf("-1\n");
            lessThan = 1;
            break;  // 一旦发现小于的情况，就退出循环
        }
        s3[i] = s2[i];  // 复制s2到s3
    }

    if (!lessThan) {
        s3[n] = '\0';  // 确保s3以null字符结尾
        puts(s3);
    }

    return 0;
}
