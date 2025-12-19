#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int min,max;
}cow;

typedef struct
{
    int num,spf;
}lotion;

int cmp(const void *a,const void *b){
    cow *ca=(cow *)a;
    cow *cb=(cow *)b;

    if(ca->max > cb->max)
        return 1;
    if(ca->max < cb->max)
        return -1;
    return ca->min - cb->min;
}

int cmp2(const void *a,const void *b){
    lotion * la=(lotion *)a;
    lotion * lb=(lotion *)b;

    return (lb->spf - la->spf);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    cow nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].min,&nums[i].max);
    }
    qsort(nums+1,n,sizeof(cow),cmp);
    lotion a[m+1];
    for(int i=1;i<=m;i++){
        scanf("%d %d",&a[i].spf,&a[i].num);
    }
    qsort(a+1,m,sizeof(lotion),cmp2);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[j].num>0&&(a[j].spf>=nums[i].min&&a[j].spf<=nums[i].max)){
                ans++;
                a[j].num--;
                break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

