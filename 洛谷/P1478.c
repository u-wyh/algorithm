#include<stdlib.h>
#include<stdio.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m,x,y;
    scanf("%d %d %d %d",&n,&m,&x,&y);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        if(a[i]>x+y)
            b[i]=1e9;
    }
    qsort(b+1,n,sizeof(int),cmp);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(m>=b[i])
        {
            ans++;
            m-=b[i];
        }
        else
            break;
    }
    printf("%d\n",ans);
    return 0;
}
