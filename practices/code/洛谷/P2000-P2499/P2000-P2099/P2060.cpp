// https://www.luogu.com.cn/problem/P2060
// 题意：给定起点和终点，在无限棋盘上每步按马走日，
// 一个坐标变化 1、另一个变化 2，正负方向任选。求到终点所需的最少步数。
// 数据范围：四个输入坐标都在 [1,10^7]，移动途中允许经过负坐标。
// 难度评分：1700（洛谷分级换算）
// 算法标签：数学、递归

#include<bits/stdc++.h>
using namespace std;

int go(int x,int y)
{
    if (x == 1 && y == 0) { return 3; }
    if (x == 2 && y == 2) { return 4; }
    if(y<=x-y){
    	if(x%2==0) {
            return x/2+(x/2-y)%2;
        }
        if(x%2==1) {
            return (x+1)/2+((x+1)/2-y+1)%2;
        }
    }
    if(y>x-y) {
        return go(x+1,y-1);
    }
}

int main()
{
    int x1,x2,y1,y2;
    cin>>x1>>y1>>x2>>y2;
    int a,b;
    a=max(abs(x1-x2),abs(y1-y2));
    b=min(abs(x1-x2),abs(y1-y2));
    cout<<go(a,b);
    return 0;
}
