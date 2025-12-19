#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

bool check(int x,int *nums,int limit,int L,int v){
    for(int i=1;i<=x;i++){
        L+=nums[i];
        if((L*1.0/v-limit)>0)
            return true;
    }
    return false;
}

int main()
{
    int n,L,v;
    scanf("%d %d %d",&n,&L,&v);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    int m;
    scanf("%d",&m);
    int t;
    for(int i=1;i<=m;i++){
        scanf("%d",&t);
        int l=0,r=n,mid,ans=-1;
        if(L*1.0/v>t){
            printf("0\n");
            continue;
        }
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(mid,a,t,L,v)){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
