#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define Max 100000+5

typedef struct
{
    int v,w;
}people;

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

bool check(int limit,people *nums,int n){
    int a[Max],b[Max],m=0,k=0;
    for(int i=1;i<=n;i++){
        if(nums[i].v>limit){
            a[m++]=(nums[i].v+nums[i].w-limit);
        }else if(nums[i].v<limit){
            b[k++]=nums[i].w;
        }
    }
    if(m<k){
        return false;
    }
    qsort(a,m,sizeof(int),cmp);
    qsort(b,k,sizeof(int),cmp);
    int i=0,j=0;
    while (i < k && j < m) {
        if (a[j] < b[i]) return false;  // 如果背负者的速度小于被背负者的体重，则无法背负
        i++;
        j++;
    }
    return true;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n,max=0,min=1e9;
        scanf("%d",&n);
        people nums[n+1];
        for(int i=1;i<=n;i++){
            scanf("%d %d",&nums[i].v,&nums[i].w);
            max=max>nums[i].v?max:nums[i].v;
            min=min<nums[i].v?min:nums[i].v;
        }
        int l=min,r=max,mid,ans=min;
        while(l<=r){
            mid=(l+r)/2;
            if(check(mid,nums,n)){
                ans=mid;
                l=mid+1;
            }else {
                r=mid-1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
