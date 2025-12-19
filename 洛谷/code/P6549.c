#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int ans=n;
    for(int i=n;i>=1;i--){
        if(a[i]==ans){
            ans--;
        }
    }
    printf("%d\n",ans);
    return 0;
}
