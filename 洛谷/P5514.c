#include<stdio.h>

int main()
{
    int n,ans;
    scanf("%d %d",&n,&ans);
    int a;
    for(int i=2;i<=n;i++){
        scanf("%d",&a);
        ans^=a;
    }
    printf("%d\n",ans);
    return 0;
}
