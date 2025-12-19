#include<bits/stdc++.h>

using namespace std;
struct programmer
{
	char lc;
	char rc;
}lt[130];
char h,h1;
void sm(char x)
{
	if(x=='*') return;
	cout<<x;
	sm(lt[x].lc);
	sm(lt[x].rc);
}
int main()
{
	int n;
	scanf("%d",&n);
	cin>>h1;
	cin>>lt[h1].lc;
	cin>>lt[h1].rc;
	for(int i=2;i<=n;i++)
	{
		cin>>h;
		cin>>lt[h].lc;
		cin>>lt[h].rc;
	}
	sm(h1);
	return 0;
}
