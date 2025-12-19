#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char a,b;
}card;

int cmp(const void *a,const void *b){
    card *ca=(card *)a;
    card *cb=(card *)b;

    if(ca->b > cb->b)
        return 1;
    if(ca->b < cb->b)
        return -1;
    return ca->a - cb->a;
}

int main()
{
    int n;
    scanf("%d",&n);
    getchar();
    card nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%c%c",&nums[i].a,&nums[i].b);
        getchar();
    }
    qsort(nums+1,n,sizeof(card),cmp);
/*
    printf("--------------------------------------\n");
    for(int i=1;i<=n;i++)
    {
        printf("%c%c\n",nums[i].a,nums[i].b);
    }
    printf("---------------------------------------\n");
*/
    int ans=0,count1=0,count2=1;
    for(int i=2;i<=n;i++){
        if(nums[i].b==nums[i-1].b){
            count2++;
            if(nums[i].a==nums[i-1].a){
                count1++;
            }
        }else{
            //printf("%d %d\n",count1,count2);
            if(count2-count1*2>=count1){
                ans+=count1;
            }else{
                ans+=count2-2*count1+2*(count1*3-count2)/3;
            }
            count1=0;
            count2=1;
        }
    }
    //printf("%d %d\n",count1,count2);
    if(count2-count1*2>=count1){
        ans+=count1;
    }else{
        ans+=count2-2*count1+2*(count1*3-count2)/3;
    }
    printf("%d\n",ans);
    return 0;
}
