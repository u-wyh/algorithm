// https://www.luogu.com.cn/problem/P1248
// 题意：n 个产品依次先在 A 车间加工（耗时 A_i），
// 再在 B 车间加工（耗时 B_i）。
// 题意：每个车间同一时刻只能加工一个产品，
// 求完成全部产品加工的最短总时间及顺序（SPJ）。
// 输入：第一行输入 n，第二行输入 n 个整数 A_i，
// 第三行输入 n 个整数 B_i。
// 输出：第一行输出最短加工总时间，
// 第二行输出一种合法的产品加工顺序（1..n 排列）。
// 数据范围：1 <= n <= 1000。
// 数据范围：1 <= A_i, B_i <= 1000。
// 难度评分：1600（洛谷分级换算）
// 算法标签：贪心、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

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
        nums[i].a=read();
    }
    for(int i=1;i<=n;i++){
        nums[i].b=read();
        nums[i].op=(nums[i].a<nums[i].b)?1:2;
        nums[i].id=i;
    }
    sort(nums+1,nums+n+1,cmp);
    int ta=0,tb=0;
    for(int i=1;i<=n;i++){
        ta+=nums[i].a;
        tb=max(ta,tb)+nums[i].b;
    }
    cout<<tb<<endl;
    for(int i=1;i<=n;i++){
        cout<<nums[i].id<<' ';
    }
    return 0;
}