#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

bool check(int num){
    for(int i=2;i*i<=num;i++){
        if(num%i==0)
            return false;
    }
    return true;
}

int main()
{
    int n,k,ans=0;
    scanf("%d %d",&n,&k);
    int nums[n+1],U=(1<<n)-1;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    for(int s=0;s<=U;s++){
        if(__builtin_popcount(s)==k){
            int sum=0;
            for(int i=1;i<=n;i++){
                if((1<<(i-1))&s)
                    sum+=nums[i];
            }
            if(check(sum))
                ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
