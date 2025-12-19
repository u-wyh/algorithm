#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}time;

int cmp1(const void *a,const void *b){
    time *ta=(time *)a;
    time *tb=(time *)b;

    return tb->b - ta->b;
}

int cmp2(const void *a,const void *b){
    time *ta=(time *)a;
    time *tb=(time *)b;

    return ta->a - tb->a;
}

int cmp3(const void *a,const void *b){
    time *ta=(time *)a;
    time *tb=(time *)b;

    return (ta->a+ta->b)-(tb->a+tb->b);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n,T;
        scanf("%d %d",&n,&T);
        time nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d %d",&nums[i].a,&nums[i].b);
        }
        qsort(nums+1,n,sizeof(time),cmp1);
        int i;
        for(i=1;i<=n;i++){
            if(nums[i].b<0)
                break;
        }
        qsort(nums+1,i-1,sizeof(time),cmp2);
        qsort(nums+i,n-i+1,sizeof(time),cmp3);
        for(i=1;i<=n;i++){
            if(T>=nums[i].a&&T>0){
                T+=nums[i].b;
            }else{
                printf("-1s\n");
                break;
            }
            if(i==n){
                if(T>0)
                    printf("+1s\n");
                else{
                    printf("-1s\n");
                }
            }
        }
    }
    return 0;
}
