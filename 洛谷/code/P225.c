#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}cow;

int cmp(const void *a,const void *b){
    cow * ga=(cow *)a;
    cow * gb=(cow *)b;

    if(ga->b > gb->b)
        return 1;
    if(ga->b < gb->b)
        return -1;
    return (gb->a-ga->a);
}

int main()
{
    int n;
    scanf("%d",&n);
    cow nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(cow),cmp);
    int ans=2;
    int t1=nums[1].b,t2=nums[2].b;
    for(int i=3;i<=n;i++){
        if(t1>t2){
            if(nums[i].a>=t1){
                ans++;
                t1=nums[i].b;
            }else if(nums[i].a>=t2){
                ans++;
                t2=nums[i].b;
            }
        }else{
            if(nums[i].a>=t2){
                ans++;
                t2=nums[i].b;
            }else if(nums[i].a>=t1){
                ans++;
                t1=nums[i].b;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
