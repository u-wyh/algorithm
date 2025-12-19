#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int k=1,ans=0;
    for(int i=1;i<=m;i++)
    {
        if(b[i]>=a[k])
        {
            ans+=b[i];
            k++;
        }
        if(k==n+1)
            break;
    }
    if(k<=n)
        printf("you died!\n");
    else
        printf("%d\n",ans);
    return 0;
}
