#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int d,g;
}milk;

int max(int a,int b){
    return a>b?a:b;
}

int cmp(const void *a,const void *b){
    milk *ma=(milk *)a;
    milk *mb=(milk *)b;

    return mb->g-ma->g;
}

int main()
{
    int n,t=0;
    scanf("%d",&n);
    milk nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d",&nums[i].g,&nums[i].d);
        t=max(t,nums[i].d);
    }
    qsort(nums+1,n,sizeof(milk),cmp);
    int used[t+1];
    for(int i=1;i<=t;i++){
        used[i]=0;
    }
    used[0]=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(used[nums[i].d]==0){
            used[nums[i].d]=1;
            ans+=nums[i].g;
        }else{
            while(nums[i].d>=1){
                nums[i].d--;
                if(used[nums[i].d]==0){
                    used[nums[i].d]=1;
                    ans+=nums[i].g;
                    break;
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
