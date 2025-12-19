#include<bits/stdc++.h>
using namespace std;

long long n,m,nm,k,as,x,h[200010],s[200010],ans=0,c,ss[500010];

int main()
{
	cin>>n>>m>>nm>>k;
	ss[0]=n;
	for(int i=1;i<=nm;i++)
	{
		cin>>as>>x;
		if(as==1) {
			h[x]++;
			ss[h[x]-1]--;//涂过h[x]-1次的行数减1
			ss[h[x]]++;//涂过h[x]次的行数加1
		}
		else
            s[x]++;
	}
	sort(h+1,h+n+1);//从小到大排序
	ans=n*m;//答案初始化
	for(int i=1;i<=m;i++){
		c=s[i]%k;
		for(int j=(k-c)%k;j<=h[n];j+=k){
			ans=ans-ss[j];
		}
	}
	cout<<ans;

	return 0;
}
