// https://www.luogu.com.cn/problem/P8837
// 题意：输入正整数 n, m、n 人的预算 w_1..w_n 和 m 个物品的价格
// c_1..c_m；
// 每人至多买一件、每个物品
// 至多被买一次（w_i >= c_j 时人 i 可买物品 j），
// 输出最多有多少人能买到物品（注：原文输出格式处误印数据范围
// 按题意与样例输出一个整数）。
// 数据范围：1 <= n, m <= 10^5，w_i, c_i <= 10^9。
// 算法标签：排序、贪心、双指针
#include<stdio.h>
#include<stdlib.h>

int cmp(const void * a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int j=1;j<=m;j++){
        scanf("%d",&b[j]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int i=1,j=1,cnt=0;
    while(i<=n&&j<=m){
        if(a[i]>=b[j]){
            i++;
            j++;
            cnt++;
        }
        else{
            j++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
