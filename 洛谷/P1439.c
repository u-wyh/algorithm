#include<stdio.h>
#include<stdbool.h>

#define MAX 100000+5

int a[MAX],b[MAX];
int n;

bool check(int x){
    int k=1,ans=0;
    for(int i=1;i<=n;i++){
        if
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }
    int l=1,r=n,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
