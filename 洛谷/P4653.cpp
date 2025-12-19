#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int n,l,r;//l：A组,r:B组
double a[N],b[N],ans,suma,sumb;

inline bool cmp(double i,double j){
	return i>j;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
        scanf("%lf%lf",&a[i],&b[i]);
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n,cmp);
	for(r=1;r<=n;r++){//双指针
		sumb+=b[r];
		ans=max(ans,min(suma-(l+r),sumb-(l+r)));
		while(suma<sumb&&l<n){//尝试选择当前总价值低的那组
			suma+=a[++l];
			ans=max(ans,min(suma-(l+r),sumb-(l+r)));
		}
	}
	printf("%.4lf\n",ans);
	return 0;
}
