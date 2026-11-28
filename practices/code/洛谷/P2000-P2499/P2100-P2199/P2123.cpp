// https://www.luogu.com.cn/problem/P2123
// 题意：T 组数据，每组有 n 位大臣，
// 第 i 位左手正整数 a_i、右手正整数 b_i。
// 奖金 c_1 = a_1 + b_1，
// c_i = max(c_{i-1}, sum_{j=1..i} a_j)
// + b_i（2 <= i <= n）。
// 可重排大臣顺序（允许不改），求获得奖金最多的大臣所获奖金的最小值。
// 数据范围：T <= 10，1 <= n <= 2 * 10^4，
// 1 <= a_i, b_i <= 10^9。
// 难度评分：1900（洛谷分级换算）
// 算法标签：贪心、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25005;

int n;
struct node{
    int a,b,op,id;
};
node nums[MAXN];

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

bool cmp(node a,node b){
    if(a.op!=b.op){
        return a.op<b.op;
    }
    if(a.op==1){
        return a.a<b.a;
    }
    else{
        return a.b>b.b;
    }
}

int main()
{
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i].a=read(),nums[i].b=read();
            nums[i].op=(nums[i].a<nums[i].b)?1:2;
            nums[i].id=i;
        }
        sort(nums+1,nums+n+1,cmp);
        long long ta=0,tb=0;
        for(int i=1;i<=n;i++){
            ta+=nums[i].a;
            tb=max(ta,tb)+nums[i].b;
        }
        cout<<tb<<endl;
    }
    return 0;
}