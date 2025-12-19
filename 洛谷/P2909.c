#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n,m,D,L,ans=0;
    scanf("%d %d %d %d",&n,&m,&D,&L);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    for(int i=1;i<=m;i++){
        int s=0;
        for(int j=1;j<=n;j++){
            if(!nums[j])
                continue;
            if(nums[j]-s*D>=L){
                s++;
                ans++;
                nums[j]=0;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
