#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(long long *)b-*(long long  *)a);
}

int main()
{
    int c,n,k;
    scanf("%d %d %d",&c,&n,&k);
    long long a[n+1],sum[n+1],ans=0;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    qsort(a+1,n,sizeof(long long),cmp);
    sum[0]=0;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=a[k]){
            ans=(a[k]-a[i]);
        }else{
            ans+=((k-i)*a[i]-sum[k]+sum[i]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
