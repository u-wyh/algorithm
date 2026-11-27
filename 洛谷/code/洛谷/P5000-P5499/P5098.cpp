// https://www.luogu.com.cn/problem/P5098
// 题意：给定平面上 N 个整点坐标，
// 求任意两点间曼哈顿距离 |x_1-x_2| + |y_1-y_2| 的最大值。
// 数据范围：1 <= N <= 50000，
// -10^6 <= x, y <= 10^6。
// 算法标签：曼哈顿距离转切比雪夫距离、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;

int x[MAXN];
int y[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        x[i]=a+b;
        y[i]=a-b;
    }
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    cout<<max(y[n]-y[1],x[n]-x[1])<<endl;
    return 0;
}