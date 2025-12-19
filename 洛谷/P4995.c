#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
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
    long long ans=nums[1]*nums[1];
    int l=1,r=n;
    while(l<r){
        ans+=pow(nums[l]-nums[r],2);
        l++;
        ans+=pow(nums[l]-nums[r],2);
        r--;
    }
    printf("%lld\n",ans);
    return 0;
}
