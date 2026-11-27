// https://www.luogu.com.cn/problem/P5635
// 题意：两人轮流操作数 x, y（mod p），奇数轮 x = (x+y) mod p，偶数轮 y = (x+y) mod p，先变成 0 者胜
// 永不到 0 则平局。
// 输入 T, p 及 T 组初始 (x, y)；每组输出 1（cbw 胜）、2（zhouwc 胜）或 error（平局）。
// 数据范围：1 <= T <= 200，1 <= x, y, p <= 10000。
#include<bits/stdc++.h>
// 算法标签：记忆化搜索、博弈论
using namespace std;

int t,mod,x,y;
short book[10005][10005];

int fun(int x,int y){
    if(book[x][y]==-1)
        return -1;
    if(book[x][y])
        return book[x][y];
    book[x][y]=-1;
    if(!x){
        book[x][y]=1;
        return 1;
    }
    if(!y){
        book[x][y]=2;
        return 2;
    }
    int num=(x+y)%mod;
    book[x][y]=fun(num,(num+y)%mod);
    return book[x][y];
}

int main()
{
    cin>>t>>mod;
    while(t--){
        cin>>x>>y;
        int ans=fun(x,y);
        if(ans==-1){
            cout<<"error"<<endl;
        }else
            cout<<book[x][y]<<endl;
    }
    return 0;
}
