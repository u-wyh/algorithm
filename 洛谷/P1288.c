#include<stdio.h>

int main()
{
    int n,cnt=0;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    for(int i=1;i<=n;i++){
        if(nums[i]==0)
            break;
        else{
            cnt++;
        }
    }
    if(cnt%2==0){
        printf("NO\n");
    }else{
        printf("YES\n");
    }
    return 0;
}
