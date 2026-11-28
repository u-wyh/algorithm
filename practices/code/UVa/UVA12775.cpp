// https://onlinejudge.org/external/127/12775.pdf
// 题意：每组给三种礼物的单价 A、B、C 和总预算 P。
// 每种礼物可购买任意非负整数件。
// 求总价恰好为 P 的购买方案数。
// 输出：第 k 组按 Case k: 答案 的格式输出。
// 数据范围：T <= 100，
// 1 <= A, B, C, P <= 10^8，
// C / gcd(A, B, C) >= 200。
// 难度评分：1900（估算）
// 算法标签：扩展欧几里得、枚举
#include<bits/stdc++.h>
using namespace std;
#define int long long

int A,B,C,P;
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

// ax + by = n 的非负整数解数量
int solve(int a,int b,int n){
    exgcd(a,b);

    if(n%d!=0){
        return 0;
    }

    int k=n/d;

    // 一组特解
    int x0=x*k;

    int dx=b/d;
    int dy=a/d;

    // 调整成最小非负 x
    x0=(x0%dx+dx)%dx;

    // 根据 x0 算出对应 y0
    int y0=(n-a*x0)/b;

    if(y0<0){
        return 0;
    }

    return y0/dy+1;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    for(int Case=1;Case<=T;Case++){
        cin>>A>>B>>C>>P;

        int g=__gcd(__gcd(A,B),C);

        int ans=0;

        if(P%g==0){
            A/=g;
            B/=g;
            C/=g;
            P/=g;

            for(int z=0;z*C<=P;z++){
                int n=P-z*C;
                ans+=solve(A,B,n);
            }
        }

        cout<<"Case "<<Case<<": "<<ans<<'\n';
    }

    return 0;
}