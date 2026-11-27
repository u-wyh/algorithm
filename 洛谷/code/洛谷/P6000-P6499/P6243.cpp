// https://www.luogu.com.cn/problem/P6243
// 题意：N 头奶牛依次进行两道挤奶工序（两道工序的牛序必须相同），
// 第 i 头牛两道工序耗时分别为 A_i, B_i，
// 求最优排队后挤完所有奶牛的最短总时间。
// 数据范围：1 <= N <= 25000，
// 1 <= A_i, B_i <= 2*10^4。
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