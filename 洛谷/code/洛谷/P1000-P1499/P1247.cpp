// https://www.luogu.com.cn/problem/P1247
// 题意：k 堆火柴各有 n_i 根，双方轮流从某一堆取至少 1 根，
// 取走最后一根者胜（Nim 博弈）。
// 题意：判断先手是否必胜；
// 若必胜，输出第一次取走后能留给对手必败态的字典序最小方案。
// 输入：第一行输入正整数 k，第二行输入 k 个整数 n_1..n_k。
// 输出：先手必败输出 lose；
// 必胜则第一行输出 a b（从第 b 堆取 a 根，b 最小且 a 最小），
// 输出：第二行输出取完后各堆剩余火柴数。
// 数据范围：
// k <= 500000，
// n_i <= 10^9（洛谷题面未显式标注下界，按正整数计）。
// 算法标签：博弈论、位运算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
int val[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    int eor=0;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        eor^=val[i];
    }
    if(eor){
        for(int i=1;i<=n;i++){
            if((eor^val[i])<=val[i]){
                cout<<(val[i]-(eor^val[i]))<<' '<<i<<endl;
                for(int j=1;j<=n;j++){
                    int v=val[j];
                    if(i==j){
                        v=eor^val[i];
                    }
                    cout<<v<<' ';
                }
                cout<<endl;
                return 0;
            }
        }
    }
    else{
        cout<<"lose"<<endl;
    }
    return 0;
}