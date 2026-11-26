// https://www.luogu.com.cn/problem/P3800
// 题意：第一行输入棋盘行数 N、列数 M、P 点个数 K、每秒最大左右移动格数 T；
// 接下来 K 行每行输入 x, y, v 表示第 x 行第 y 列有价值为 v 的 P 点（每格最多 1 个）。
// 初始可从第 1 行任意格出发，每秒必须下移一行，并可在下移同时向左或右瞬间移动至多 T 格（也可不动，不经过途中格，只拾取目标格 P 点）。
// 输出能获得的所有 P 点价值总和的最大值。
// 数据范围：对于 100% 的测试点，1 <= N, M, T, K <= 4000，0 <= v <= 100。
#include<bits/stdc++.h>
using namespace  std;

int n,m,k,t;
int nums[4005][4005];

inline int read(){
	int fl=1,w=0;char ch=getchar();
	while(!isdigit(ch) && ch!='-') ch=getchar();
	if(ch=='-') fl=-1;
	while(isdigit(ch)){w=w*10+ch-'0',ch=getchar();}
	return fl*w;
}

int main()
{
    n=read(),m=read(),k=read(),t=read();
    int x,y,m;
    for(int i=1;i<=k;i++){
        cin>>x>>y>>m;
        nums[x][y]=m;
    }

    return 0;
}
