#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005

int n,q,u;
long long x[MAXN],sum[MAXN];
long long a,b;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
	}	
	sort(x+1,x+n+1);
   
	for(int i=1;i<=n;i++){ 
		sum[i]=sum[i-1]+x[i];
	}
   
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>a>>b;
		u=(int)(ceil((long double)b*n/(a+b))); 
		cout<<(x[u]*(u)-sum[u])*a+(sum[n]-sum[u]-x[u]*(n-u))*b<<endl;
	}
	
	return 0;
}