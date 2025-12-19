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

