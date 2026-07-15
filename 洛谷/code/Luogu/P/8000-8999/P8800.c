#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

bool judge(int limit,int *a,int *b,int n,long long m){
    for(int i=1;i<=n;i++){
        if((limit-a[i]>b[i])||(limit-a[i]>m)||m<0)
            return false;
        else if(a[i]>=limit){
            continue;
        } else {
            m-=(limit-a[i]);
        }
    }
    return true;
}

int main()
{
    int n;
    long long m;
    scanf("%d %lld",&n,&m);
    int a[n+1],b[n+1],l=1e9,r=-1,mid,ans;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        l=min(l,a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        r=max(r,a[i]+b[i]);
    }
    while(l<=r){
        mid=l+((r-l)>>1);
        if(judge(mid,a,b,n,m)){
            ans=mid;
            l=mid+1;
        } else {
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
