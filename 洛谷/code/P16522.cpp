// https://www.luogu.com.cn/problem/P16522
// 题意：给定 n 条直线 y = k_i*x + b_i，多次查询过指定点 (x, y) 的直线条数。
// 输入：首行 n，后 n 行给 (k_i, b_i)，再 Q 及 Q 行询问点 (x, y)。
// 规则：统计有多少条直线满足 y = k_i*x + b_i。
// 输出：共 Q 行，依次输出每次询问经过该点的直线数量。
// 数据范围：1 <= n, Q <= 2*10^5，|x|, |y|, |k_i|, |b_i| <= 2*10^4（时限 3.0s）。
// 算法标签：根号分治、计数统计
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 405;
const int MAXB = 4e4+5;

int n,m;
int small[MAXN][MAXB];
int large[MAXN][MAXB];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int k,b;
        cin>>k>>b;
        if(abs(k)<=200){
            small[k+200][b+20000]++;
        }
        else{
            int limit=40000/abs(k);
            for(int x=-limit;x<=limit;x++){
                int y=k*x+b;
                if(-20000<=y&&y<=20000){
                    large[x+200][y+20000]++;
                }
            }
        }
    }
    cin>>m;
    while(m--){
        int x,y;
        cin>>x>>y;
        int ans=0;
        if(abs(x)<=200){
            ans+=large[x+200][y+20000];
        }
        int lim=200;
        if(x!=0){
            lim=min(200,40000/abs(x));
        }

        for(int k=-lim;k<=lim;k++){
            int b=y-k*x;
            if(-20000<=b&&b<=20000){
                ans+=small[k+200][b+20000];
            }
        }

        cout<<ans<<'\n';
    }
    return 0;
}