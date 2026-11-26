// https://www.luogu.com.cn/problem/P9975
// 题意：N 头奶牛排成一排，给定长度为 N 的 01 串表示若干晚后各牛是否被感染（1 感染，0 未感染）。
// 初始有若干头牛被感染，每过一晚，每头已感染的牛都会同时传染给左右紧邻的牛（若存在）。
// 求初始最少可能有多少头牛被感染。
// 题意：第一行输入 N，第二行输入长度为 N 的 01 串；输出一个整数。
// 数据范围：1 <= N <= 3 * 10^5。
#include<stdio.h>
#include<stdbool.h>

#define MAX 300000+5

char s[MAX];
int n;

bool check(int x){

}

int main()
{
    scanf("%d",&n);
    scanf("%s",s);
    int l=0,r=n,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

