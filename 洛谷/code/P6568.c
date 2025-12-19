#include<stdio.h>

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+2],sum[n+1],ans=0;
    nums[n+1]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        if(i<=k+1){
            sum[k]+=nums[i];
            ans=max(ans,sum[k]+nums[i+1]);
        }else{
            sum[i]=sum[i-1]+nums[i]-nums[i-k];
            ans=max(ans,sum[i]+nums[i+1]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
