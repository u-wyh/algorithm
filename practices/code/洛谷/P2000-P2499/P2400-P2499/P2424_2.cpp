// https://www.luogu.com.cn/problem/P2424
// 题意：f(X) 表示 X 的所有正约数之和，
// 给定正整数 X, Y (X < Y)。
// 求 f(X) + f(X+1) + ... + f(Y) 的值。
// 输出约数和的总和。
// 数据范围：1 <= X < Y <= 2*10^9。
// 难度评分：1700（洛谷分级换算）
// 算法标签：数论分块、前缀和
#include<bits/stdc++.h>
using namespace std;
typedef __int128 i128;

int x,y;

i128 solve(int n){
    if(n==0){
        return 0;
    }
    i128 ans=0;
    i128 t=1;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;

        ans+=t*v*(rt-lt+1)*(1ll*lt+rt)/2;
    }
    return ans;
}

void print(i128 x){
    if(x==0){
        cout<<0;
        return ;
    }

    if(x<0){
        cout<<'-';
        x=-x;
    }

    string s;
    while(x){
        s.push_back('0'+x%10);
        x/=10;
    }

    reverse(s.begin(),s.end());
    cout<<s;
}

int main()
{
    cin>>x>>y;
    i128 ans=0;
    ans=solve(y);
    ans-=solve(x-1);
    print(ans);
    return 0;
}