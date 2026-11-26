// https://www.luogu.com.cn/problem/P2114
// 题意：有 n 扇防御门，每扇门为一种位运算 op（AND/OR/XOR）和参数 t。
// 初始攻击力 x 可任选 [0,m] 中的整数，依次经过所有防御门后变为最终伤害。
// 求一次攻击最多能造成多少伤害。
// 数据范围：2 <= n <= 10^5，0 <= m <= 10^9，0 <= t <= 10^9。
#include<bits/stdc++.h>
using namespace std;

int n,m,ans,x,a1=0,a2=-1;
char str[5];

int main()
{
	scanf("%d%d",&n,&m);
	while(n--){
		scanf("%s%d",str,&x);
		if(str[0]=='A') a1&=x, a2&=x;
		if(str[0]=='X') a1^=x, a2^=x;
		if(str[0]=='O') a1|=x, a2|=x;
	}
	for(int j=29;~j;--j){
		if(a1>>j&1)
            ans+=1<<j;
		else if(a2>>j&1&&(1<<j)<=m)
            ans+=1<<j, m-=1<<j;
	}
	printf("%d",ans);
	return 0;
}
