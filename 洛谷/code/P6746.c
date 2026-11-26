// https://www.luogu.com.cn/problem/P6746
// 题意：给定非负整数 a, b，可执行两种操作任意次（过程中允许变成负数）：1) 花费 c 将两数同减任意正整数 x；
// 2) 花费 d 选正整数 x 将一数乘 x、另一数除以 x 后向下取整。
// 求使 a, b 都变为 0 的最小总代价。
// 数据范围：0 <= a, b, c, d <= 10^9。
#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    if(a==0&&b==0){
        printf("0\n");
    }else if(a*b==0){
        printf("%d\n",d);
    }else if(a==b){
        printf("%d\n",min(c,2*d));
    }else{
        printf("%d\n",min(c+d,2*d));
    }
    return 0;
}
