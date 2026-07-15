#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int k=1;k<=t;k++)
    {
        int n,p;
        scanf("%d %d",&n,&p);
        if(n<2*p+1)
        {
            printf("-1\n");
        }
        else
        {
            int nums[n+1];
            for(int i=1;i<=n;i++)
            {
                nums[i]=0;
            }
            int j=n;
            for(int i=0;i<=p;i++)
            {
                nums[j]=1;
                j-=2;
            }
            for(int i=1;i<=n;i++)
            {
                printf("%d",nums[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
