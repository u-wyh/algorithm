#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int m,v;
    double div;
}gold;

int cmp(const void *a,const void *b){
    gold * ga=(gold *)a;
    gold * gb=(gold *)b;

    return gb->div - ga->div;
}

int main()
{
    int n,t;
    scanf("%d %d",&n,&t);
    gold nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].m,&nums[i].v);
        nums[i].div=1.0*nums[i].v/nums[i].m;
    }
    qsort(nums+1,n,sizeof(gold),cmp);
    double ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].m<=t){
            t-=nums[i].m;
            ans+=nums[i].v*1.0;
        }else{
            ans+=nums[i].div*t;
            t=0;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
