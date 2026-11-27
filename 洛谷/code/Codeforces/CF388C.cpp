// https://codeforces.com/problemset/problem/388/C
// 题意：n 堆卡牌，每堆有 s_i 张带分值牌，Ciel 取顶牌，
// Jiro 取底牌。
// 规则：两人轮流取牌（Ciel 先手），双方均最大化自身总分。
// 输出：两人最终各自的总得分。
// 数据范围：1 <= n, s_i <= 100，
// 1 <= c_k <= 1000。
// 算法标签：博弈论、贪心、排序
#include<bits/stdc++.h>
using namespace std;

int n;
int a,b;
int top;
int nums[105];

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

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    n=read();
    while(n--){
        int t;
        t=read();
        for(int i=1;i<=t/2;i++){
            a+=read();
        }
        if(t%2==1){
            nums[++top]=read();
        }
        for(int i=1;i<=t/2;i++){
            b+=read();
        }
    }
    sort(nums+1,nums+top+1,cmp);
    for(int i=1;i<=top;i+=2){
        a+=nums[i];
    }
    for(int i=2;i<=top;i+=2){
        b+=nums[i];
    }
    printf("%d %d",a,b);
    return 0;
}