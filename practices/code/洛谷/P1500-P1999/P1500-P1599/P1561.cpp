// https://www.luogu.com.cn/problem/P1561
// 题意：有 N 个对象，每个先用时 U[i] 上山，再用时 D[i] 下山。
// 任何时刻上山段、下山段各最多一人，两段可以同时有人。
// 可在山顶等待，两个阶段的顺序都可以安排。
// 求全部完成所需的最短时间。
// 数据范围：1 ≤ N ≤ 25000，
// 1 ≤ U[i],D[i] ≤ 50000。
// 难度评分：1600（洛谷分级换算）
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