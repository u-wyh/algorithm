#include<stdio.h>

int main()
{
    int n,cnt=0;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    int k1,k2;
    for(int i=1;i<=n;i++){
        if(nums[i]==0){
            k1=i;
            break;
        }
    }
    for(int i=n;i>=1;i--){
        if(nums[i]==0){
            k2=(n-i+1);
            break;
        }
    }
    if(k1%2==1&&k2%2==1){
        printf("NO\n");
    }else{
        printf("YES\n");
    }
    return 0;
}

