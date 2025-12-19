#include<stdio.h>
#include<math.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int a,b,x,y;
    scanf("%d %d %d %d",&a,&b,&x,&y);
    int ans=abs(a-b);
    ans=min(ans,abs(a-x)+abs(b-y));
    ans=min(ans,abs(a-y)+abs(b-x));
    printf("%d\n",ans);
    return 0;
}
