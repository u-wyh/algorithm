#include<stdio.h>

double max(double a,double b){
    return a>b?a:b;
}

int check(double x,double *nums,int n,int k){
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=(int)(nums[i]/x);
        if(ans>=k)
            return ans;
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    double nums[n+1],r=0,l=0,mid,ans;
    for(int i=1;i<=n;i++){
        scanf("%lf",&nums[i]);
        r=max(r,nums[i]);
    }
    while(r-l>=1e-4){
        mid=(l+r)/2;
        if(check(mid,nums,n,k)>=k){
            l=mid;
            ans=mid;
        }else{
            r=mid;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
