#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    long long ans=0;
    if(n%2==0){
        for(int i=1;i<=n/2;i++){
            if(nums[i]<=0)
                break;
            else{
                ans+=nums[i];
            }
        }
    }else{
        for(int i=1;i<=n/2+1;i++){
            if(nums[i]<=0)
                break;
            else{
                ans+=nums[i];
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
