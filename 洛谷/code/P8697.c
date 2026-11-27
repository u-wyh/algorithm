// https://www.luogu.com.cn/problem/P8697
// 题意：输入两个非空大写英文字母字符串 S 和 T，输出 T 从首字符开始最长有多少个连续字符构成的前缀是 S 的子序列。
// 数据范围：1 <= |T| <= |S| <= 1000。
// 算法标签：贪心、双指针
#include<stdio.h>
#include<string.h>
#define Max 1005

int main()
{
    char s1[Max],s2[Max];
    fgets(s1,Max,stdin);
    fgets(s2,Max,stdin);
    int n=strlen(s1);
    int m=strlen(s2);
    int k=0;
    for(int i=0;i<n;i++)
    {
        if(s2[k]==s1[i])
            k++;
        if(k==m-1)
            break;
    }
    printf("%d\n",k);
    return 0;
}
