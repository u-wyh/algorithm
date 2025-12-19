#include<stdio.h>

int check(int n){
    int ans=n;
    while(n>=3){
        ans+=n/3;
        n=n%3+n/3;
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    int l=1,r=n,ans=n,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)>=n){
            ans=mid;
            r=mid-1;
        }else {
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

