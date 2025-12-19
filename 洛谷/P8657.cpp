#include<bits/stdc++.h>
using namespace std;

int n, m, a, b, sum, d[100];

int main()
{
	cin>>n>>m;
	while(m--) cin>>a>>b, d[a] ++, d[b] ++;
	for(int i = 1;i <= n;i ++) sum += d[i];
	for(int i = 1;i <= n;i ++) printf("%.12lf\n", 1.0*sum/d[i]);
	return 0;
}

