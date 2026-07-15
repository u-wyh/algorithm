#include<bits/stdc++.h>
int t,n,q;
int x,y;
int gcd(int a,int b)
{
	while(b^=a^=b^=a%=b);
	return a;
}
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>q;
		for(int i=1;i<=q;i++)
		{
			cin>>x>>y;
			cout<<x+y-2*gcd(x,y)<<'\n';
		}
	 }
	return 0;
}
