// https://www.luogu.com.cn/problem/P8686
// 题意：输入 N 和数组 A_1..A_N
// 从 i=2 到 N 依次处理 A_i：若当前 A_i 在 A_1..A_{i-1} 中出现过则持续加 1 直到未出现过为止，输出最终的 A_1..A_N。
// 数据范围：1 <= N <= 10^5，1 <= A_i <= 10^6。
// 算法标签：并查集
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 1000005

int fa[Max];

int find(int x)//并查集中的查询操作{
	if(x==fa[x])
        return x;
	return
        fa[x]=find(fa[x]);
}

int main()
{
    for(int i=0;i<=1000005;i++)
        fa[i]=i;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int a;
        scanf("%d",&a);
        a=find(a);
        fa[a]=find(a)+1;
        printf("%d ",a);
    }
    return 0;
}

