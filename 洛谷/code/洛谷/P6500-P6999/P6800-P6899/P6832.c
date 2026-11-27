// https://www.luogu.com.cn/problem/P6832
// 题意：给定一个由小写字母组成的字符串 S，
// 求 S 中出现次数最多的非空子串的出现次数。
// 数据范围：0 < |S| <= 10^7，字符属于 [a, z]。
// 算法标签：计数、模拟
#include<stdio.h>
#include<string.h>
#define Max 10000005

int main()
{
    char s[Max];
    fgets(s,Max,stdin);
    int n=strlen(s)-1;
    long long nums[26];
    long long ans=0;
    for(int i=0;i<26;i++)
        nums[i]=0;
    for(int i=0;i<n;i++)
    {
        nums[s[i]-'a']++;
    }
    for(int i=0;i<26;i++)
        ans=ans>nums[i]?ans:nums[i];
    printf("%lld\n",ans);
    return 0;
}
