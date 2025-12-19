#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}food;

int cmp(const void *a,const void *b){
    food * fa=(food *)a;
    food * fb=(food *)b;

    if(fa->a > fb->a)
        return -1;
    if(fa->a < fb->a)
        return 1;

    return fa->b - fb->a;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int limit[k+1];
    for(int i=1;i<=k;i++){
        scanf("%d",&limit[i]);
    }
    food nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(food),cmp);
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++){
        if(limit[nums[i].b]>=1){
            ans+=nums[i].a;
            cnt++;
            limit[nums[i].b]--;
        }
        if(cnt==m)
            break;
    }
    printf("%d\n",ans);
    return 0;
}
