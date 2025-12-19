#include<stdio.h>

int work(int *a,int n){
    int ans=0;
    int b[n];
    for(int k=20;k>=0;k--){
        int top=0;
        for(int i=1;i<=n;i++){
            if(a[i]&(1<<k))
                b[++top]=a[i];
        }
        if(top>=2){
            ans=b[1]&b[2];
        }
        break;
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i]);
        }
        printf("Case #%d: %d\n",i,work(nums,n));
    }
    return 0;
}
