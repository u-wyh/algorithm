// https://www.luogu.com.cn/problem/P3167
// 题意：输入一个含小写字母以及通配符 '*'（匹配 0 个及以上任意字符）和 '?'（匹配恰好 1 个任意字符）的模式串
// 再输入文件数量 n 及 n 个仅含小写字母的文件名字符串。
// 依次判断每个文件名能否被该通配符模式串完全匹配。
// 输出 n 行，匹配成功输出 YES，否则输出 NO。
// 数据范围：字符串长度不超过 100000，1 <= n <= 100，通配符个数不超过 10。
#include <bits/stdc++.h>
// 算法标签：字符串哈希、动态规划
using namespace std;
#define ULL unsigned long long
const int maxn = 1e5+10;
ULL h1[maxn],h2[maxn],p[maxn];

const ULL P = 131;
ULL get(int l, int r,ULL h[] )
{
	if( r<l )	return 0;
    return h[r] - h[l - 1] * p[r - l + 1];
}

int num,q,m,n,f[12][maxn],id[maxn];
char t[maxn],s[maxn];
int main()
{
    p[0] = 1;
    for(int i = 1; i <= 100000; i ++ )    p[i] = p[i - 1] * P;
    scanf("%s%d",t+1,&q);
    n = strlen( t+1 ); t[++n] = '?';
    for(int i=1;i<=n;i++)	if( t[i]=='*'||t[i]=='?' )	id[++num] = i;//通配符下标

    for(int i=1;i<=num;i++)
   	for(int j=id[i-1]+1;j<=id[i]-1;j++)
	   	h1[i] = h1[i]*P+t[j];//字符串hash
   	while( q-- )
   	{
		scanf("%s",s+1); m = strlen( s+1 ); s[++m] = 'k';
		memset( f,0,sizeof f );
		for(int i=1;i<=m;i++)	h2[i] = h2[i-1]*P+s[i];

		f[0][0] = 1;
		for(int i=0;i<num;i++)//枚举匹配到第几个通配符
	   	for(int j=0;j<=m;j++)
	   	{
	   		if( f[i][j]==0 )	continue;//无法进行转移
	   		if( f[i][j]==2 )	f[i][j+1] = 2;//传递下去,后面都是符合的
	   		int r = j+id[i+1]-id[i]-1;
	   		if( h1[i+1]!=get(j+1,r,h2) )	continue;//必须匹配两个通配符中间的字母
			if( t[id[i+1]]=='?' )	f[i+1][r+1] = 1;//'?'也必须匹配掉,所以是r+1
			else		f[i+1][r] = 2;//'*'可以为空,所以是r
		}
		if( f[num][m] )	printf("YES\n");
		else	printf("NO\n");
	}
}
