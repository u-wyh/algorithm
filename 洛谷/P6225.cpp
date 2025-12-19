#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=2e5+5;
int n,Q;
int a[MAXN];

class BIT
{
	private:
	int tree[MAXN];
	public:
	int lowbit(const int x)
	{
		return x&-x;
	}
	void modify(int pos,const int x)
	{
		for(;pos<=n;pos+=lowbit(pos))
		 tree[pos]^=x;//维护异或和
	}
	int query(int pos)
	{
		int res=0;
		for(;pos;pos-=lowbit(pos))
		 res^=tree[pos];//同理
		return res;
	}
}tree[2];//tree[0]是维护下标为偶数，tree[1]则是奇数

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>Q;
	for(int i=1;i<=n;i++)
	 cin>>a[i];
	for(int i=1;i<=n;i++)
	 tree[i&1].modify(i,a[i]);//建树
	while(Q--)
	{
		int opt,x,y;cin>>opt>>x>>y;
		if(opt==1)
		{
			tree[x&1].modify(x,a[x]^y);//解释过了
			a[x]=y;
		}
		if(opt==2)
		{
			int ans=0;
			if(!((x&1)^(y&1)))//l,r奇偶性相同
			 ans=tree[x&1].query(y)^tree[x&1].query(x-1);
			cout<<ans<<endl;
		}
	}
	return 0;
}
