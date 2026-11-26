// https://www.luogu.com.cn/problem/P1196
// 题意：有 30000 艘战舰，开始时各自成列。
// M i j 把 i 所在整列接到 j 所在列的尾部，列内顺序保持原样。
// C i j 查询同列时两舰之间的战舰数，不同列输出 -1。
// 数据范围：1 ≤ T ≤ 5 × 10^5，1 ≤ i, j ≤ 30000，i ≠ j，合并前两舰分属不同列。

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 30005

int father[Max],size[Max],stack[Max];

void build()
{
    for(int i=0;i<=Max;i++)
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
    int n;
    scanf("%d",&n);
    char str[n+1];
    int a[n+1],b[n+1];
    build();
    for(int i=1;i<=n;i++)
    {
        scanf("%c %d %d",&str[i],&a[i],&b[i]);
        if(str[i]=='M')
        {
            un(a[i],b[i]);
        }
        if(str[i]=='C')
        {
            if(issameset(a[i],b[i]))
            {
                printf("%d\n",size[b[i]]-size[a[i]]);
            }
            else
            {
                printf("-1\n");
            }
        }
        scanf("\n");
    }
    return 0;
}
