// https://www.luogu.com.cn/problem/P5656
// 题意：T 组询问，
// 求解不定方程 ax + by = c 的整数解情况（无整数解输出 -1；
// 有整数解无正整数解输出最小正整数 x 和最小正整数 y；
// 有正整数解输出解数、x 最小值、y 最小值、x 最大值、y 最大值）。
// 输入 T 及各组 a, b, c；对应输出 T 行答案。
// 数据范围：1 <= T <= 2*10^5，
// 1 <= a, b, c <= 10^9。
// 难度评分：1700（洛谷分级换算）
// 算法标签：扩展欧几里得、数论
#include<bits/stdc++.h>
using namespace std;
#define int long long

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
    int T;
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        exgcd(a,b);
        if(c%d==0){
            x=c/d*x;
            y=c/d*y;
            int dx=b/d;
            int dy=a/d;

            if(x<=0){
                int delta=(dx-x)/dx;
                x+=delta*dx;
                y-=delta*dy;
            }
            else{
                int delta=(x-1)/dx;
                x-=delta*dx;
                y+=delta*dy;
            }

            if(y<=0){
                cout<<x<<' ';
                y+=(dy-y)/dy*dy;
                cout<<y<<endl;
            }
            else{
                cout<<((y-1)/dy+1)<<' ';
                int xmin,xmax,ymin,ymax;
                xmin=x;
                ymax=y;

                int delta=(y-1)/dy;
                y-=dy*delta;
                x+=dx*delta;
                xmax=x;
                ymin=y;
                cout<<xmin<<' '<<ymin<<' '<<xmax<<' '<<ymax<<endl;
            }
        }
        else{
            cout<<-1<<endl;
        }
    }
    return 0;
}