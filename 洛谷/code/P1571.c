#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

bool binarysearch(int *b,int m,int x){
    int l=1,r=m;
    while(l<=r){
        int mid=l+((r-l)>>1);
        if(b[mid]==x){
            return true;
        }else if(b[mid]>x){
            r=mid-1;
        }else {
            l=mid+1;
        }
    }
    return false;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1];
    int b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int j=1;j<=m;j++){
        scanf("%d",&b[j]);
    }
    qsort(b+1,m,sizeof(int),cmp);
    for(int i=1;i<=n;i++){
        if(!binarysearch(b,m,a[i]))
            continue;
        else
            printf("%d ",a[i]);
    }
    return 0;
}
