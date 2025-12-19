#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct
{
    int a,b,c;
}planet;

int cmp(const void *a,const void *b){
    planet * pa=(planet *)a;
    planet * pb=(planet *)b;

    if(pa->b > pb->b)
        return 1;
    if(pa->b < pb->b)
        return -1;
    return pb->c-pa->c;
}

int main()
{
    int n,p,a,b;
    scanf("%d %d",&n,&p);
    planet nums[n+1];
    for(int i=1;i<=n;i++){
        if(i==p){
            scanf("%d %d",&a,&b);
        }
        else{
            scanf("%d %d",&nums[i].a,&nums[i].b);
            nums[i].c=nums[i].a-nums[i].b;
        }
    }
    nums[p].a=0,nums[p].b=INT_MAX,nums[p].c=INT_MIN;
    int cnt=1,ans=a;
    qsort(nums+1,n,sizeof(planet),cmp);
    for(int i=1;i<=n;i++){
        if(nums[i].c<0){
            continue;
        }
        if(ans<nums[i].b){
            break;
        }else{
            ans+=nums[i].c;
            cnt++;
        }
    }
    printf("%d\n%d\n",ans,cnt);
    return 0;
}
