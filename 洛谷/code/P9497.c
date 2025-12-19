#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        qsort(a[i],n,sizeof(int),cmp);
    }
    while(m--){
        int x;
        scanf("%d",&x);
        int k=0;
        for(int i=0;i<n;i++){
            int l=0,r=n-1,mid,ans=-1;
            while(l<=r){
                mid=l+((r-l)>>1);
                if(a[i][mid]>=x){
                    ans=mid;
                    l=mid+1;
                }else{
                    r=mid-1;
                }
            }
            k+=(ans+1);
        }
        if(k>n)
            printf("%d\n",n);
        else
            printf("%d\n",k);
    }
    return 0;
}
