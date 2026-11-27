// https://www.luogu.com.cn/problem/P3467
// 题意：输入自西向东紧挨着排成一排的建筑数量 n，以及每栋建筑的宽度 d_i 和高度 w_i。
// 用若干条边平行于坐标轴、互不重叠（允许边缘相接）且不能超出墙面的矩形海报，完全覆盖所有建筑的北立面。
// 输出一个整数，表示最少需要多少张矩形海报。
// 数据范围：1 <= n <= 2.5*10^5，1 <= d_i, w_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：单调栈
using namespace std;
int n,sol,x,y;
stack<int>s;
int main()
{
    scanf("%d",&n);
    while(n--)
	{
        scanf("%d %d",&y,&x);
        while(!s.empty()&&s.top()>x)
            s.pop();
        if(!s.empty()&&s.top()==x)
            continue;
        if(x)
            sol++,s.push(x);
    }
    printf("%d",sol);
    return 0;
}
