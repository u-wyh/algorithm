#include<stdio.h>
#include<math.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a1[n+1],a2[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a1[i]);
        a2[n-i+1]=a1[i];
    }
    int ans1=0,ans2=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        ans1+=(a1[i]!=b[i])?1:0;
        ans2+=(a2[i]!=b[i])?1:0;
    }
    printf("%d\n",ans1<ans2?ans1:ans2);
    return 0;
}
