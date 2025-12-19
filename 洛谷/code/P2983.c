#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    long long p,c;
}chocolate;

int cmp(const void *a,const void *b){
    chocolate * ca=(chocolate *)a;
    chocolate * cb=(chocolate *)b;

    return ca->p - cb->p;
}

int main()
{
    int n;
    long long m;
    scanf("%d %lld",&n,&m);
    chocolate nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&nums[i].p,&nums[i].c);
    }
    qsort(nums+1,n,sizeof(chocolate),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(m>=nums[i].p*nums[i].c){
            m-=nums[i].p*nums[i].c;
            ans+=nums[i].c;
        }else if(m>=nums[i].p){
            ans+=m/nums[i].p;
            m=0;
        }else{
            break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
