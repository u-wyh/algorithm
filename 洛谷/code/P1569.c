#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int d[n+1];
    d[0]=0;
    int f[n+1];
    int x;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        d[i]=d[i-1]+x;
        if(d[i]>0)
            f[i]=1;
        else
            f[i]=0;
    }
    if(d[n]<0)
    {
        printf("Impossible\n");
        return 0;
    }
    for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(f[j]>0&&d[i]-d[j]>=0)//前面已经可以分组&&这一段理智>=0
			f[i]=max(f[i],f[j]+1);//更新最大值
		}
	}
	printf("%d\n",f[n]);
    return 0;
}
