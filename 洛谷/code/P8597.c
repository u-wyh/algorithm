// https://www.luogu.com.cn/problem/P8597
// 题意：输入两行等长仅含 * 和 o 的字符串分别表示初始态和目标态，每次可同时翻转相邻两个字符，输出变为目标态的最少步数（数据保证有解）。
// 数据范围：每行字符串长度小于 1000（题面未给出更多数据范围限制）。
// 算法标签：贪心、模拟
#include<stdio.h>
#include<string.h>
#define Max 105

int main()
{
    char s1[Max],s2[Max];
    fgets(s1,Max,stdin);
    fgets(s2,Max,stdin);
    int n=strlen(s1)-1,count=0;
    for(int i=0;i<n-1;i++)
    {
        if(s1[i]!=s2[i])
        {
            count++;
            if(s1[i+1]=='*')
                s1[i+1]='o';
            else
                s1[i+1]='*';
        }
    }
    printf("%d\n",count);
    return 0;
}
