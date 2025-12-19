#include<bits/stdc++.h>
using namespace std;
int n,m;
string s;
struct Tree
{
     int fail;
     int vis[30];
     int end;
}tree[1500000];
int cnt=1;
void build(string s)//将字符串s加入字典树
{
	int l=s.size();//获取s的长度
	int now=1;//now指针设为1
	for(int i=0;i<l;++i)
	{
		if(tree[now].vis[s[i]-'a']==0)//没有建边
			tree[now].vis[s[i]-'a']=++cnt;
		now=tree[now].vis[s[i]-'a'];//跳转
	}
	tree[now].end+=1;//结尾处加上1
}
int getans(string s)//获取结果
{
	int l=s.size();
	int now=1,ans=0;//同build
	for(int i=0;i<l;++i)
	{
		now=tree[now].vis[s[i]-'a'];//跳转
		for(int t=now;t&&tree[t].end!=-1;t=tree[t].fail)//每次都跳fail指针
		{
			ans+=tree[t].end;//加上结尾的，即统计答案
		}
	}
	return ans;
}
int main()//主函数没什么能讲的了OVO
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		build(s);
	}
	while(m--)
	{
		cin>>s;
		cout<<getans(s)<<'\n';
	}
	return 0;//华丽丽的结束
}
