#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    long long sum=0,eor=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        sum+=nums[i];
        eor^=nums[i];
    }
    if(sum==n){
        if(n%2==0){
            printf("lose\n");
        }else{
            printf("1 1\n");
            printf("0 ");
            for(int i=2;i<=n;i++){
                printf("1 ");
            }
        }
    }else{
        if(eor==0){
            printf("lose\n");
        }else{
            int k=1;
            while(eor>=(1<<k)){
                k++;
            }
            k--;
            for(int i=1;i<=n;i++){
                if(nums[i]&(1<<k)){
                    printf("%d %d\n",(nums[i]-(nums[i]^eor)),i);
                    nums[i]=(nums[i]^eor);
                    break;
                }
            }
            for(int i=1;i<=n;i++){
                printf("%d ",nums[i]);
            }
        }
    }
    return 0;
}
