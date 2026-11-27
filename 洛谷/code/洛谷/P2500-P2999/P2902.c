// https://www.luogu.com.cn/problem/P2902
// 题意：输入偶数珍珠总数 N、颜色种数 C，
// 以及每种颜色 i 拥有的珍珠数 C_i。
// 将所有 N 颗珍珠配成 N/2 对，
// 要求每对中的两颗珍珠颜色不同（数据保证存在答案）。
// 构造任意一种合法的配对方案。
// 输出共 N/2 行，每行两个整数 a_i, b_i，表示该对两颗珍珠的颜色编号。
// 数据范围：对于 100% 的数据，2 <= N <= 10^5 且 N 为偶数，
// 1 <= C <= N。
// 算法标签：构造
#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+2],b[m+1],k=1;
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
        while(b[i]--){
            a[k++]=i;
        }
    }
    for(int i=1;i<=n/2;i++){
        printf("%d %d\n",a[i],a[i+n/2]);
    }
    return 0;
}
