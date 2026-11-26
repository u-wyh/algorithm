// https://www.luogu.com.cn/problem/P9753
// 题意：给定长度为 n 的小写字母串。
// 若一个字符串可以通过反复删除两个相邻的相同字符（剩余部分拼接）最终变成空串，则称其为可消除的。
// 求原串中有多少个非空连续子串是可消除的。
// 题意：第一行输入 n，第二行输入字符串；输出一行一个整数。
// 数据范围：1 <= n <= 2 * 10^6。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n;
char str[MAXN];
int g[MAXN];
long long f[MAXN];

int main()
{
    scanf("%d",&n);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++){
        int pos=i-1;
        while(pos>0){
            if(str[pos]==str[i]){
                g[i]=pos;
                break;
            }
            else{
                pos=g[pos]-1;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<g[i]<<' ';
    // }
    // cout<<endl;
    // f[0]=-1;
    for(int i=1;i<=n;i++){
        if(g[i]){
            f[i]=f[g[i]-1]+1;
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<f[i]<<' ';
    // }
    // cout<<endl;
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=f[i];
    }
    cout<<ans<<endl;
    return 0;
}