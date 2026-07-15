#include <stdio.h>
#include <stdlib.h>

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1],maxans=0;
        long long sum=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i]);
            maxans=max(maxans,nums[i]);
            sum+=nums[i];
        }
        if(maxans<=sum/2&&n%2==1){
            printf("NO\n");
        }else{
            printf("YES\n");
        }
    }
    return 0;
}
