// https://www.luogu.com.cn/problem/P5650
// 题意：给定一个非空 01 串 S，找出它的非空连续子串 T，使得 T 中 '0' 的个数减去 '1' 的个数最大。
// 输入 01 串 S；输出这个最大差值。
// 数据范围：1 <= |S| <= 10^5。
#include<stdio.h>
#include<string.h>

#define MAX 100000+5

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    char s[MAX];
    scanf("%s",s);
    int ans=0,n=strlen(s),maxans=-1;
    for(int i=0;i<n;i++){
        if(s[i]=='0')
            ans+=1;
        else{
            ans-=1;
        }
        maxans=max(maxans,ans);
        if(ans<0)
            ans=0;
    }
    printf("%d\n",maxans);
    return 0;
}
