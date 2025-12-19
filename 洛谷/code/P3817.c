#include<stdio.h>

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    nums[0]=0;
    long long ans=0;
    for(int i=0;i<n;i++){
        if((nums[i]+nums[i+1])>m)
        {
            ans+=(nums[i]+nums[i+1]-m);
            nums[i+1]=m-nums[i];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
