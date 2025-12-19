#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=3e5+5;

map <int,int> mp;
int n,a[N]; ll ans;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],mp[a[i]]++;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		ll tmp=a[i],cnt=0;
		while(mp[tmp]){
			cnt+=tmp*mp[tmp],mp[tmp]=0;
			if(tmp%2==0)tmp=tmp/2*3;
			else break;
		}
		ans=max(ans,cnt);
	} cout<<ans<<endl;
	return 0;
}
