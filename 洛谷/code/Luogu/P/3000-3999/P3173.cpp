#include<iostream>
#include<cstdio>
using namespace std;
size_t a[10010],b[10010],sum=0,n,m;
int main() {
	cin>>n>>m;
	n--,m--;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		sum+=b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum+=min(a[i],b[j]);
		}
	}
	cout<<sum<<endl;
	return 0;
}
