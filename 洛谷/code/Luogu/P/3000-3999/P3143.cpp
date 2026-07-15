#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,a[50005],c[50005],r=2,ma,ans;//c[i]用来存从i-1向左最多可以取多少颗钻石。
int main(){
    scanf("%d %d",&n,&k);
	a[n+1]=2100000000;
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        while(a[r]<=a[i]+k)r++;
        c[r]=max(r-i,c[r]);
        ma=max(ma,c[i]);
        ans=max(ans,ma+r-i);
    }
    printf("%d",ans);
    return 0;
}
