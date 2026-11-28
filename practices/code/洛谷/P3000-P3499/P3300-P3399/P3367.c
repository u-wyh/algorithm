// https://www.luogu.com.cn/problem/P3367
// 题意：输入元素数 N 和操作数 M，维护 1..N 的并查集。
// 每次操作输入 Z_i、X_i、Y_i：
// Z_i=1 时合并 X_i 和 Y_i 所在集合，
// Z_i=2 时查询二者是否同集。
// 对每个 Z_i=2 的操作输出一行 'Y' 或 'N'。
// 数据范围：1 <= N <= 2*10^5，1 <= M <= 10^6，
// 1 <= X_i, Y_i <= N，Z_i ∈ {1, 2}。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 200005

int father[Max],size[Max],stack[Max];

void build(int n)
{
    for(int i=1;i<=n;i++)
    {
        father[i]=i;
        size[i]=1;
    }
}

int find(int i)
{
    int size=0;
    while(i!=father[i])
    {
        stack[size++]=i;
        i=father[i];
    }
    while(size>0)
    {
        father[stack[--size]]=i;
    }
    return i;
}

bool issameset(int x,int y)
{
    return find(x)==find(y);
}

void un(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy)
    {
        if(size[fx]>=size[fy])
        {
            size[fx]+=size[fy];
            father[fy]=fx;
        }
        else
        {
            size[fy]+=size[fx];
            father[fx]=fy;
        }
    }
}


int main()
{
    int n,m;
    scanf("%d %d",&m,&n);
    int a[n+1],b[n+1],c[n+1];
    build(n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        if(a[i]==1)
        {
            un(b[i],c[i]);
        }
        if(a[i]==2)
        {
            if(issameset(b[i],c[i]))
                printf("Y\n");
            else
                printf("N\n");
        }
    }

    return 0;
}
