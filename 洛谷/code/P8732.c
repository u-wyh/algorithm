#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int s,a,e;
}student;

int cmp(const void *a,const void *b){
    student * sa=(student *)a;
    student * sb=(student *)b;

    return (sa->s+sa->a+sa->e)-(sb->s+sb->a+sb->e);
}

int main()
{
    int n;
    scanf("%d",&n);
    student nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&nums[i].s,&nums[i].a,&nums[i].e);
    }
    qsort(nums+1,n,sizeof(student),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=(n-i+1)*(nums[i].a+nums[i].s+nums[i].e);
        ans-=nums[i].e;
    }
    printf("%lld\n",ans);
    return 0;
}
