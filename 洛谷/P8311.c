#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1],minans=1e9;
    long long sum=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        minans=min(minans,nums[i]);
        sum+=nums[i];
    }
    sum-=minans;
    sum+=minans*(n-1);
    printf("%lld\n",sum);
    return 0;
}
