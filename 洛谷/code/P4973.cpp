// https://www.luogu.com.cn/problem/P4973
// 题意：定义「X-* 进制」字符串 s 的值为 prod_{i=0}^{n-1} (X^i * (ASCII(s_i) - 48))，共有 Q 次询问
// 每次给定 X_i 和字符串 s_i（字符 ASCII > 48），求其十进制表示的数字位数。
// 数据范围：1 <= Q <= 100，1 <= X_i = |s_i| - 1 <= 10^5。
#include<bits/stdc++.h>
// 算法标签：数学、对数
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        int x;
        string str;
        cin>>x>>str;
        int n=str.length();
        long double ans=1;
        ans+=1.0*(n-1)*n/2*log10(x);
        for(int i=0;i<n;i++){
            ans+=log10(str[i]-'0');
        }
        cout<<(long long)ans<<endl;
    }
    return 0;
}