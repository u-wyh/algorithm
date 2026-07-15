#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}num;

int cmp(const void *a,const void *b)
{
    num * na=(num *)a;
    num * nb=(num *)b;

    return ((na->a+na->b)-(nb->a+nb->b));
}

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    num nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(num),cmp);
    long long  ans=0;
    for(int i=1;i<=n/2;i++){
        ans+=min(nums[i].a,nums[i].b);
    }
    for(int i=n/2+1;i<=n;i++){
        ans-=max(nums[i].a,nums[i].b);
    }
    printf("%lld\n",ans);
    return 0;
}
