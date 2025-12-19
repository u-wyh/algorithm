#include<stdio.h>
#include<stdlib.h>

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    long long ans=0;
    for(int i=n;i>=1;i--){
        int k=0,m=nums[i];
        if(m==0)
            continue;
        for(int j=i;j>=1;j--){
            if(nums[j]==0)
                continue;
            k+=min(m,nums[j]);
            if(nums[j]<=m)
                nums[j]=0;
            else
                nums[j]-=m;
        }
        ans+=k*i;
    }
    printf("%lld\n",ans);
    return 0;
}
