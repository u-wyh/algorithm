#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int check(int limit,int *nums,int m,int n,int d){
    int sum=0;
    for(int i=1;i<=n;i++){
        if(sum>=m){
            return true;
        }
        for(int j=1;j<=limit;j++){
            if(nums[sum]<=i&&sum<m){
                if(nums[sum]+d<i){
                    return false;
                }else{
                    sum++;
                }
            }else {
                break;
            }
        }
    }
    return sum >= m;
}

int main()
{
    int n,d,m;
    scanf("%d %d %d",&n,&d,&m);
    int nums[m+1];
    for(int i=1;i<=m;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,m,sizeof(int),cmp);
    /*
    for(int i=1;i<=m;i++){
        printf("%3d",nums[i]);
    }
    printf("\n");
    */
    nums[0]=0;
    int l=0,r=m,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid,nums,m,n,d)){
            ans=mid;
            r=mid-1;
        } else {
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
