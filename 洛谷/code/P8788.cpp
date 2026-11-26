// https://www.luogu.com.cn/problem/P8788
// 题意：结果填空题，输入大写字母 `'A'` 或 `'B'` 输出对应试题答案。
// 试题 A：28 个孩子对应 28 把钥匙，随机分配有 28! 种方案，求恰有 14 个孩子分到自己钥匙的方案数；
// 试题 B：在字母 `abcdefghijklnopqr`（a..r 去掉 m 共 17 个字母）构成的环形全排列序列中（首尾相邻
// 每次可移至前一个或后一个排列）
// 求从排列 `aejcldbhpiogfqnkr` 到 `ncfjboqiealhkrpgd`（原文在 h 与 k 间多一空格）的最少转移次数。
// 数据范围：仅两道固定填空题（A、B）。
#include<bits/stdc++.h>
using namespace std;

long long f[20];
long long fac[18];
int tree[19];

inline int lowbit(int x){
    return x&(-x);
}

void add(int x,int val){
    while(x<=18){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

long long compute(string s){
    for(int i=1;i<=18;i++){
        add(i,1);
    }
    add(13,-1);
    long long ans=0;
    for(int i=0;i<17;i++){
        int x=s[i]-'a';
        if(x!=0){
            ans+=fac[16-i]*sum(x);
        }
        add(x+1,-1);
    }
    return ans;
}

int main()
{
    // long long ans1=8*17*19*23*25*27;
    // f[2]=1;
    // f[3]=2;
    // for(int i=4;i<=14;i++){
    //     f[i]=(i-1)*(f[i-1]+f[i-2]);
    // }
    // ans1*=f[14];
    // cout<<ans1<<endl;

    // fac[0]=1;
    // for(int i=1;i<=17;i++){
    //     fac[i]=(fac[i-1]*i);
    // }

    // long long x=compute("aejcldbhpiogfqnkr");
    // long long y=compute("ncfjboqiealhkrpgd");
    // cout<<x<<' '<<y<<endl;
    // long long ans2=min(y-x,fac[17]-y+x);
    // cout<<ans2<<endl;
    string ans1="1286583532342313400";
    string ans2="106148357572143";
    char op;
    cin>>op;
    cout<<(op=='A'?ans1:ans2);
    return 0;
}