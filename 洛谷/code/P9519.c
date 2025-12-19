#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

#define MAX 1000000+5

int a[MAX],b[MAX],n,m,c[MAX];

int max(int a,int b){
    return a>b?a:b;
}

int min(int a,int b){
    return a<b?a:b;
}

bool check(int x){
    for(int i=1;i<=n;i++){
        c[i]=0;
    }
    for(int i=1;i<=m;i++){
        for(int j=max(b[i]-x+1,1);j<=min(b[i]+x-1,n);j++){
            c[j]+=(x-abs(j-b[i]));
        }
    }
    for(int i=1;i<=n;i++){
        if(c[i]<a[i])
            return false;
    }
    return true;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    int l=0,r=1e9,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
