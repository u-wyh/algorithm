#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;
    int sum=0;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    //qsort(a+1,n,sizeof(int),cmp);
    int l,r;
    scanf("%d %d",&l,&r);
    if(sum>n*r||sum<n*l)
    {
        printf("-1\n");
        return 0;
    }
    int ans1=0,ans2=0,ans;
    for(int i=1;i<=n;i++)
    {
        if(a[i]>r)
            ans1+=(a[i]-r);
        if(a[i]<l)
            ans2+=(l-a[i]);
    }
    //printf("%d %d\n",ans1,ans2);
    ans=(ans1<ans2?ans1:ans2)+abs(ans1-ans2);
    printf("%d\n",ans);
    return 0;
}
