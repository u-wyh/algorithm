#include<stdio.h>

#define MAX 100000+5

int max(int a,int b){
    return a>b?a:b;
}

int n;
int nums[MAX];

int main()
{
    long long ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        ans+=max(0,nums[i]-nums[i-1]);
    }
    printf("%lld\n",ans);
    return 0;
}
