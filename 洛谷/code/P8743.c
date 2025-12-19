#include<stdio.h>
#include<string.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1],cnt[21],eor=0;
        for(int j=0;j<=20;j++){
            cnt[j]=0;
        }
        for(int j=1;j<=n;j++){
            scanf("%d",&nums[j]);
            eor^=nums[j];
            for(int k=0;k<=20;k++){
                cnt[k]+=((nums[j]>>k)&1);
            }
        }
        if(eor==0){
            printf("0\n");
        }else{
            for(int k=20;k>=0;k--){
                if(cnt[k]%2==0)
                    continue;
                if(cnt[k]==1){
                    printf("1\n");
                }else if((n-cnt[k])&1){
                    printf("-1\n");
                }else{
                    printf("1\n");
                }
                break;
            }
        }
    }
    return 0;
}
