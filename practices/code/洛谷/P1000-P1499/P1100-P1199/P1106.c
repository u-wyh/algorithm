// https://www.luogu.com.cn/problem/P1106
// 题意：给十进制整数 n，删掉恰好 k 位，剩余数字的顺序保持不变。
// 求能得到的最小非负整数，输出时去掉前导零。
// 数据范围：1 ≤ k < n 的位数 ≤ 250。
// 难度评分：1200（洛谷分级换算）
// 算法标签：单调栈、贪心

#include<stdio.h>
#include<string.h>

#define MAX 255

char s[MAX];
int nums[MAX],stack[MAX],size=0;
int k;

int main()
{
    scanf("%s",s);
    int n=strlen(s);
    scanf("%d",&k);
    //printf("%d\n",n);
    for(int i=0;i<n;i++){
        nums[i+1]=s[i]-'0';
    }
    int h=k;
    for(int i=1;i<=n;i++){
        while(k&&size&&nums[i]<stack[size]){
            k--;
            stack[size--]=0;
        }
        stack[++size]=nums[i];
    }
    int i=1;
    while(stack[i]==0&&i!=n-h)
        i++;
    for(;i<=n-h;i++){
        printf("%d",stack[i]);
    }
    return 0;
}
