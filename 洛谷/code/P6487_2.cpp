// https://www.luogu.com.cn/problem/P6487
// 题意：n 枚石子两人轮流取，先手第一次可取任意多个，之后每次至少取 1 个、至多取上一次对方所取数量的 2 倍，取走最后一块者胜。
// 求先手为保证获胜第一次最少取几颗石子。
// 数据范围：2 <= n <= 10^15。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e15;

int n;
int len;
int fib[80];
int val[80];

void prepare(){
    fib[++len]=1;
    fib[++len]=2;
    while(true){
        ++len;
        fib[len]=fib[len-1]+fib[len-2];
        if(fib[len]>INF){
            break;
        }
    }
}

signed main()
{
    prepare();
    int n,m;
    cin>>n;
    m=n;
    int cnt=0;
    for(int i=len;i>=1;i--){
        if(n>=fib[i]){
            val[++cnt]=fib[i];
            n-=fib[i];
        }
    }
    if(cnt==1){
        cout<<m<<endl;
    }
    else{
        cout<<val[cnt]<<endl;
    }
    return 0;
}