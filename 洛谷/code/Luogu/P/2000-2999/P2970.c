#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}grass;

int cmp(const void *a,const void *b){
    grass * ga=(grass *)a;
    grass * gb=(grass *)b;

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
    grass nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(grass),cmp);
    int ans=1;
    int t=nums[1].b;
    for(int i=2;i<=n;i++){
        if(nums[i].a>=t){
            ans++;
            t=nums[i].b;
        }
    }
    printf("%d\n",ans);
    return 0;
}
