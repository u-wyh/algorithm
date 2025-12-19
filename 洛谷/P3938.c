#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int k;
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        int n,m,t;
        scanf("%d %d %d",&n,&t,&m);
        int defence[n+1],a;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&defence[i]);
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&a);
            defence[a]-=2;
        }
        qsort(defence+1,n,sizeof(int),cmp);
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            if(defence[i]>0)
                ans++;
            else
            {
                if(t+defence[i]>=1)
                {
                    t+=defence[i]-1;
                    ans++;
                }
                else
                    break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
