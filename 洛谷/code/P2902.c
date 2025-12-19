#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+2],b[m+1],k=1;
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
        while(b[i]--){
            a[k++]=i;
        }
    }
    for(int i=1;i<=n/2;i++){
        printf("%d %d\n",a[i],a[i+n/2]);
    }
    return 0;
}
