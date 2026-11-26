// https://www.luogu.com.cn/problem/P1904
// 题意：读入若干建筑 (L,H,R)，分别表示左端、高度和右端。
// 每处的天际线高度取覆盖此处的最高建筑，无建筑时为 0。
// 按横坐标升序输出高度发生变化的位置及变化后的高度。
// 数据范围：1 到 5000 栋建筑，坐标为小于 10000 的正整数，每行一栋。

#include<bits/stdc++.h>
using namespace std;
int H[10005];
int main(){
	int i,a,b,h;
	while(scanf("%d%d%d",&a,&h,&b)!=EOF)
		for(i=a;i<b;++i)
            H[i]=max(H[i],h);
	for(i=1,h=0;i<1e4;++i)
		if(h!=H[i])
			h=H[i],printf("%d %d ",i,H[i]);
	return 0;
}
