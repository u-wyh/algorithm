#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    int ans=0,size=n;
    while(size>=2){
        ans+=a[size]+a[size-1];
        int k=a[size]+a[size-1];
        size--;
        int i=size-1;
        while(k>=a[i]&&i>=1){
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=k;
    }
    printf("%d\n",ans);
    return 0;
}

