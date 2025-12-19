#include<cstdio>
#include<iostream>
using namespace std;
int n,head=1,tail,ans;
long long a[2000001],s[2000001],q[2000001];
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i+=1)
        scanf("%lld",&a[i]);
    for(register int i=1;i<=n-1;i+=1)
        a[i+n]=a[i];
    for(register int i=1;i<=2*n-1;i+=1)
        s[i]=s[i-1]+a[i];
    for(register int i=1;i<=2*n-1;i+=1)
    {
        while(head<=tail&&max(i-n+1,1)>q[head])head++;
        while(head<=tail&&s[i]<=s[q[tail]])tail--;
        q[++tail]=i;
        if(i-n+1>0&&s[q[head]]-s[i-n]>=0)ans++;
    }
    printf("%d\n",ans);
    return 0;
}
