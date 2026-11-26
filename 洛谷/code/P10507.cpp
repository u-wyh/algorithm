// https://www.luogu.com.cn/problem/P10507
// 题意：给一排棋子的初始位置，Georgia 先走。每步选一颗棋子向左移动至少一格，不能越过左边界或别的棋子，也不能停在已占用格。不能动的人输，输出双方最优时的胜者。
// 数据范围：1 ≤ T ≤ 20，1 ≤ N ≤ 1000，1 ≤ P[i] ≤ 10000，各初始位置不同。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int pos[MAXN];
int dis[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>pos[i];
        }
        sort(pos+1,pos+n+1);
        int pre=0;
        for(int i=1;i<=n;i++){
            dis[i]=pos[i]-pre-1;
            pre=pos[i];
        }
        int eor=0;
        for(int i=n;i>=1;i-=2){
            eor^=dis[i];
        }
        if(eor){
            cout<<"Georgia will win"<<endl;
        }
        else{
            cout<<"Bob will win"<<endl;
        }
    }
    return 0;
}