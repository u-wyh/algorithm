#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

bool check(long long x,int *a,int n,int *b,int m,int k){
    int ans=0;
    for(int i=1,j=m;i<=n;i++){
        while((a[i]+b[j])>=x&&j>0){
            j--;
        }
        ans+=j;
        if(ans>=k)
            return false;
    }
    if(ans>=k)
        return false;
    return true;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    long long l=0,r=a[n]+b[m],mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid,a,n,b,m,k)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
