#include<bits/stdc++.h>
using namespace std;
char s[2010][80];
int f[2010],n,ans;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		f[i]=1;
		for(int j=i-1;j>=1;j--)
			if(strstr(s[i],s[j])==s[i])
				f[i]=max(f[j]+1,f[i]);
		ans=max(f[i],ans);
	}
	cout<<ans;
	return 0;
}
