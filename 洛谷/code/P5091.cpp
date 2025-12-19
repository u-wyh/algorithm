#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,m;
int b;
bool flag;

int power(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=(long long)(ans*a)%m;
		}
		a=(long long)(a*a)%m;
		b>>=1;
	}
	return ans;
}

signed main()
{
	cin>>a>>m;
	a%=m;
	int tmp=m;
	int temp=1;
	for(int i=2;i*i<=tmp;i++){
		if(tmp%i){
			continue;
		}
		temp*=(i-1);
		tmp/=i;
		while(tmp%i==0){
			temp*=i;
			tmp/=i;
		}
	}
	if(tmp>1){
		temp*=(tmp-1);
	}
	getchar();
	char ch;
	while((ch = getchar()) >= '0' && ch <= '9'){
		b=(b*10ll+ch-'0');
		if(b>=temp){
			flag=1;
			b%=temp;
		}
	}
	if(b>=temp){
		flag=1;
		b%=temp;
	}
	if(flag){
		b+=temp;
	}
	cout<<power(a,b);
	return 0;
}