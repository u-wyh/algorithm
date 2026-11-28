// https://www.luogu.com.cn/problem/P10576
// 题意：求所有满足 n 加 10120300500、n 减 10120300500
// 都是完全平方数的整数 n 之和。
// 数据范围：差值常数固定为 10120300500；填空题，只提交一个整数。
// 难度评分：900（洛谷分级换算）
// 算法标签：因数枚举、平方差公式

#include<bits/stdc++.h>
using namespace std;

__int128 c=20240601000;

void print(__int128 x){
    if(x==0) {
        cout<<0<<"\n";
        return;
    }
    string res="";
    while(x){
        res=char(x%10+'0')+res;
        x/=10;
    }
    cout<<res<<"\n";
}

int main()
{
    __int128 ans=0;
    for(__int128 i=1;i*i<=c;i++){
        if(c%i==0){
            __int128 a=i,b=c/i;
            __int128 x=(a+b)/2,y=(b-a)/2;
            if(x*x-y*y!=c){
                continue;
            }
            ans+=x*x-c/2;
        }
    }
    print(ans);
    return 0;
}