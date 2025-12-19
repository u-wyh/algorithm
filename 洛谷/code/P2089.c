#include<stdio.h>

#define FOR(i,n,m) for(int i=n;i<=m;i++)

int main()
{
    int n,ans=0;
    scanf("%d",&n);
    FOR(a,1,3) FOR(b,1,3) FOR(c,1,3) FOR(d,1,3) FOR(e,1,3)
    FOR(f,1,3) FOR(g,1,3) FOR(h,1,3) FOR(i,1,3) FOR(j,1,3)
    if(a+b+c+d+e+f+g+h+i+j==n)
        ans++;
    printf("%d\n",ans);
    FOR(a,1,3) FOR(b,1,3) FOR(c,1,3) FOR(d,1,3) FOR(e,1,3)
    FOR(f,1,3) FOR(g,1,3) FOR(h,1,3) FOR(i,1,3) FOR(j,1,3)
    if(a+b+c+d+e+f+g+h+i+j==n)
        printf("%d %d %d %d %d %d %d %d %d %d\n",a,b,c,d,e,f,g,h,i,j);
    return 0;
}
