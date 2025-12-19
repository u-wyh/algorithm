#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],sum[n+1],minans=0;
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum[i]=sum[i-1]+a[i];
        minans=min(minans,sum[i]);
    }
    if(minans>=0){
        printf("0\n");
    }else{
        printf("%d",-minans+1);
    }
    return 0;
}
