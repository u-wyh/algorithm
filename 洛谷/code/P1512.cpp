// https://www.luogu.com.cn/problem/P1512
// 题意：给一个起始日期，Adam 先走，两人轮流选日期加一天，或月份加一且保留日号。
// 加月后若日期不存在则不能走，不能越过目标，先到 2006-11-04 的人赢。
// 输出先手是否必胜的 YES 或 NO。
// 数据范围：起始日期在 1900-01-01 到 2006-11-03 之间，按公历的月份和闰年规则处理。

#include <iostream>
#include <cstdio>
using namespace std;
int t,x,y,z;
int main(){
	scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&x,&y,&z);
		if((y==9 && z==30) || (y==11 && z==30) || (y+z)%2==0)
        	printf("YES\n");
		else
        	printf("NO\n");
    }
	return 0;
}
