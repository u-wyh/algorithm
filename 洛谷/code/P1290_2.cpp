// https://www.luogu.com.cn/problem/P1290
// 题意：给定正整数 M 和 N，Stan 先手与 Ollie 轮流从较大数中减去较小数的正整数倍（结果 >= 0）。
// 题意：先使其中一个数变为 0 者获胜，双方均采用最优策略，判断每组胜者。
// 输入：第一行输入数据组数 C，接下来 C 行每行输入两个正整数 M, N。
// 输出：每组输出一行，Stan wins 或 Ollie wins。
// 数据范围：1 <= C <= 6。
// 数据范围：1 <= M, N < 2^31。
#include<bits/stdc++.h>
using namespace std;

bool check(int a,int b){
    if(a<b){
        swap(a,b);
    }
    if(a%b==0){
        return true;
    }
    if(a>2*b){
        return true;
    }
    return !check(b,a-b);
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        if(check(a,b)){
            cout<<"Stan wins"<<endl;
        }
        else{
            cout<<"Ollie wins"<<endl;
        }
    }
    return 0;
}