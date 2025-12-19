#include<stdio.h>
#include<stdlib.h>

int cmp(const void * a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int j=1;j<=m;j++){
        scanf("%d",&b[j]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int i=1,j=1,cnt=0;
    while(i<=n&&j<=m){
        if(a[i]>=b[j]){
            i++;
            j++;
            cnt++;
        }
        else{
            j++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
