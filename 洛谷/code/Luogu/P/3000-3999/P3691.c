#include<stdio.h>
#include<stdlib.h>

#define MAX 5000000+5

int m,n,a[MAX],b[MAX];

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(b+1,m,sizeof(int),cmp);
    for(int i=1;i<=n;i++){
        int l=1,r=m,mid,ans=-1;
        while(l<=r){
            mid=(l+r)/2;
            if(b[mid]>=a[i]){
                if(b[mid]==a[i]){
                    a[i]=0;
                    ans=mid;
                    break;
                }
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
    }
    int cnt=a[1]==0?0:1;
    for(int i=2;i<=n;i++){
        if(a[i]!=0&&a[i-1]==0)
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
