// https://www.luogu.com.cn/problem/P3480
// 题意：多组数据，输入组数 u；每组输入石子堆数 n 和初始单调不降的每堆石子数 a_1 <= a_2 <= ... <= a_n。
// 两人轮流从某一堆拿走任意多颗石子，但操作后仍必须保持各堆石子数非降序，无法移动者败。
// 输出 u 行，第 i 行表示第 i 组先手是否必胜，必胜输出 TAK，否则输出 NIE。
// 数据范围：1 <= u <= 10，1 <= n <= 1000，每组石子总数不超过 1000。
#include<bits/stdc++.h>
// 算法标签：博弈论、阶梯Nim、差分
using namespace std;
const int MAXN = 1e3+5;

int n;
int val[MAXN];
int diff[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            val[i]=read();
        }
        for(int i=1;i<=n;i++){
            diff[i]=val[i]-val[i-1];
        }
        int eorval=0;
        for(int i=n;i>=1;i-=2){
            eorval^=diff[i];
        }
        cout<<(eorval?"TAK":"NIE")<<endl;
    }
    return 0;
}