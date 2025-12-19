#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
const int o=100005;
double l=0,r=0,mid;
double a[o],sum[o];
bool work(double x){
	double t=0.0;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i]-x;
	}
	for(int i=k;i<=n;i++){
		t=min(sum[i-k],t);
		if(sum[i]>=t){
			return 1;
		}
	}
	return 0;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		r=max(r,a[i]);
	}
	while(r-l>1e-5){
		mid=(l+r)/2;
		if(work(mid)) l=mid;
		else r=mid;
	}
	cout<<(int)(r*1000);
	return 0;
}
