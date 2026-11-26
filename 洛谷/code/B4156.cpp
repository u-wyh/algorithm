// https://www.luogu.com.cn/problem/B4156
// 题意：有 N 架飞船，每架先从地球到火星，用时 U(i)，再从火星到天王星，用时 V(i)。
// 每段航线同一时刻各只能容纳一架飞船，飞船可在火星等候。
// 求所有飞船抵达的最早时刻。
// 数据范围：1 ≤ N ≤ 25000，1 ≤ U(i), V(i) ≤ 50000。

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
    return 0;
}