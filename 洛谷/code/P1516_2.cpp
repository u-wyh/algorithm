// https://www.luogu.com.cn/problem/P1516
// 题意：两只青蛙从环长 L 的数轴上 x、y 处出发，每次同时沿同方向分别跳 m、n 长度。求第一次落到同一点所需的跳跃次数，永远遇不到则输出 Impossible。
// 数据范围：1 ≤ x,y,m,n ≤ 2 × 10^9，x≠y，1 ≤ L ≤ 2.1 × 10^9。

#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,b,n,m,len;
int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

signed main()
{
    cin>>a>>b>>n>>m>>len;
    if(n<m){
        swap(n,m);
        swap(a,b);
    }
    exgcd(n-m,len);
    int c=b-a;

    if(c%d!=0){
        cout<<"Impossible"<<endl;
        return 0;
    }

    int dx=len/d;
    int dy=(n-m)/d;
    x=c/d*x;
    if(x<0){
        int delta=(1-x+dx-1)/dx;
        x+=dx*delta;
    }
    else{
        int delta=(x-1)/dx;
        x-=dx*delta;
    }
    cout<<x<<endl;
    return 0;
}