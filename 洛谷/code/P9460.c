#include<stdio.h>
#include<stdlib.h>
#define Max 100000+5

int cnt[Max];

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i=0;i<=n;i++){
        cnt[i]=0;
    }
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        cnt[a[i]]++;
    }
    qsort(cnt,n+1,sizeof(int),cmp);
    if(k>=cnt[0]){
        printf("pigstd\n");
        return 0;
    }
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        if(cnt[i]>=(cnt[0]-k))
            ans++;
        else
            break;
    }
    printf("%d\n",ans);
    return 0;
}
