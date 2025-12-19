#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(cnt<=nums[i]){
            cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
