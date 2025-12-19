#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
    int s,b;
}seasoning;

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    seasoning nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].s,&nums[i].b);
    }
    int U=(1<<n)-1;
    int ans1=1,ans2=0,ans=1e9;
    for(int s=1;s<=U;s++){
        for(int i=0;i<n;i++){
            if(s&(1<<i)){
                ans1*=nums[i+1].s;
                ans2+=nums[i+1].b;
            }
        }
        ans=min(ans,abs(ans1-ans2));
        ans1=1;
        ans2=0;
    }
    printf("%d\n",ans);
    return 0;
}
