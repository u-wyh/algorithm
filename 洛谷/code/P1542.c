#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
    int a,b,s;
}press;

bool check(double x,press *nums,int n){
    double t=0;
    for(int i=1;i<=n;i++){
        t+=1.0*nums[i].s/x;
        if(t>nums[i].b)
            return false;
        t=t>nums[i].a?t:nums[i].a;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d",&n);
    press nums[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&nums[i].a,&nums[i].b,&nums[i].s);
    }
    double l=0,r=1e8,mid,ans=1e8;
    while(r-l>1e-6){
        mid=(l+r)/2;
        if(check(mid,nums,n)){
            r=mid;
            ans=mid;
        }else{
            l=mid;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
