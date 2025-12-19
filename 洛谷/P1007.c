#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a - *(int *)b);
}


int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int L,n;
    scanf("%d %d",&L,&n);
    if(n==0){
        printf("0 0\n");
        return 0;
    }
    int nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int  maxans,minans=0;
    maxans=max(L+1-nums[1],nums[n]);
    for(int i=1;i<=n;i++){
        if(nums[i]>=L/2){
            minans=max(minans,L+1-nums[i]);
        }else{
            minans=max(minans,nums[i]);
        }
    }
    printf("%d %d\n",minans,maxans);
    return 0;
}
