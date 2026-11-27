// https://www.luogu.com.cn/problem/P3056
// 题意：输入一个长度为偶数的、仅由 '(' 和 ')' 组成的括号字符串。
// 每次操作可以反转任意一个位置的括号方向（'(' 变 ')' 或 ')' 变 '('）
// 平衡要求全局 '(' 与 ')' 数量相等且任意前缀中 '(' 不少于 ')'。
// 求将该字符串变为合法平衡括号串所需的最少反转次数。
// 输出一行一个整数，表示最少反转次数。
// 数据范围：对于 100% 的数据，字符串长度为偶数且不超过 100000。
#include<stdio.h>
#include<string.h>
// 算法标签：贪心、模拟

#define MAX 100000+5

int ans=0;
int size=0,len;
char str[MAX];

int main()
{
    scanf("%s",str);
    len=strlen(str);
    for(int i=0;i<len;i++){
        if(str[i]=='(')
            size++;
        else{
            if(size==0){
                ans++;
                size++;
            }
            else{
                size--;
            }
        }
    }
    printf("%d\n",ans+size/2);
    return 0;
}
