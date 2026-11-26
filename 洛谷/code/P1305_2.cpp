// https://www.luogu.com.cn/problem/P1305
// 题意：输入一棵二叉树，每行给一个节点字符以及它的左右孩子。首行描述的是根，没有孩子用星号。输出先序遍历，即先根、再左树、再右树。
// 数据范围：1 ≤ n ≤ 26。

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
