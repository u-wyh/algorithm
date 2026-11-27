// https://www.luogu.com.cn/problem/P9539
// 题意：给定长度为 n 的小写字母串 s 及整数 l, r。
// 构造一个长度为 n 的小写字母串 t，
// 使得满足 s_i = t_i 的位置数量在 [l, r] 之间
// 且 t 的字典序尽可能小（保证 0 <= l <= r <= n，恒有解）。
// 题意：第一行输入 n, l, r，第二行输入字符串 s；输出一行一个字符串 t。
// 数据范围：1 <= n <= 10^6，0 <= l <= r <= n。
// 算法标签：贪心、构造
#include<stdio.h>
#include<string.h>

int main()
{
    int n,l,r,n1=0,min,max;
    scanf("%d %d %d",&n,&l,&r);
    getchar();
    min=n-r;
    max=n-l;
    char s1[n+1],s2[n+1];
    for(int i=0;i<n;i++)
    {
        scanf("%c",&s1[i]);
        s2[i]=s1[i];
        if(s1[i]=='a')
            n1++;
    }
    //printf("%c\n",s2[n-1]);
    s1[n]='\0';
    s2[n]='\0';
    if(n-n1<min)
    {
        for(int i=n-1,j=0;i>=0,j<(min-n+n1);i++)
        {
            if(s1[i]=='a')
            {
                s1[i]='A';
                j++;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(s1[i]!='A'||s1[i]!='a')
                s1[i]='a';
            else if(s1[i]=='A')
                s1[i]='b';
        }
    }
    else if(min<=(n-n1)&&max>=(n-n1))
    {
        for(int i=0;i<n;i++)
            s2[i]='a';
    }
    else
    {
        for(int i=0,j=0;i<n&&j<max;i++)
        {
            if(s1[i]!='a')
            {
                s2[i]='a';
                j++;
            }
        }
    }
    //printf("%c\n",s2[n-1]);
    puts(s2);
    return 0;
}
