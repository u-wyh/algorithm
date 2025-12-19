#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    if(m>=n-1){
        printf("0\n");
        return 0;
    }
    long long  ans=2e9;
    int j=1,i;
    for(i=1;i<=min(n,m+1);i++){
        j=j>i?j:i;
        while((i-1+n-j+min(i-1,n-j))>m)
            j++;
        ans=min(ans,a[j]-a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}

