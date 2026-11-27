// https://www.luogu.com.cn/problem/P4697
// 题意：地面上沿 x_1 < x_2 < ... < x_n 顺序依次充气，第 i 个气球半径上限为 r_i，碰到前面气球或达上限即停
// 求各气球最终半径（误差 <= 10^-3）。
// 数据范围：1 <= n <= 200000，0 <= x_i <= 10^9，1 <= r_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：单调栈、数学
using namespace std;
const int MAXN = 2e5+5;

int n;
double x[MAXN];
double r[MAXN];
double ans[MAXN];

int sta[MAXN];
int top;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>r[i];
    }

    for(int i=1;i<=n;i++){
        ans[i]=r[i];
        while(top){
            int j=sta[top];
            ans[i]=min(ans[i],(x[i]-x[j])*(x[i]-x[j])/(4*ans[j]));
            if(ans[i]>ans[j]){
                top--;
            }
            else{
                break;
            }
        }
        sta[++top]=i;
    }

    cout<<fixed<<setprecision(4);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}