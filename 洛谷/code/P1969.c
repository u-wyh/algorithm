#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0,a,last=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        if(a>last){
            ans+=a-last;
        }
        last=a;
    }
    printf("%d\n",ans);
    return 0;
}
