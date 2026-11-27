// https://www.luogu.com.cn/problem/P1198
// 题意：维护一个初始为空的整数序列，依次执行 M 次操作（t 为最近一次查询答案，初值 0）。
// 题意：Q L 表示查询当前数列末尾 L 个数中的最大值并输出（保证 0 < L <= 当前长度）。
// 题意：A n 表示将 (n + t) mod D 插入数列末尾（n 可为负数）。
// 输入：第一行输入 M, D，接下来 M 行每行描述一个 Q 或 A 操作。
// 输出：对每次 Q 操作按顺序输出一行最大值结果。
// 数据范围：1 <= M <= 2 * 10^5，1 <= D <= 2 * 10^9。
// 数据范围：n 在长整型范围内。
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#define ll long long
// 算法标签：ST表、倍增
using namespace std;
ll a[200001],f[200001][21],t,D;
int n,m;
bool flag;
void change(int u){  //用change函数来进行修改
    f[u][0]=a[u];
    for(int i=1;u-(1<<i)>=0;i++)
        f[u][i]=max(f[u][i-1],f[u-(1<<(i-1))][i-1]);
}
ll find(int x,int y){
    double t=log(y-x+1)/log(2);
    int K=t;
    return max(f[y][K],f[x+(1<<K)-1][K]);
}
int main(){
    memset(f,0,sizeof(f));
    scanf("%d%lld",&m,&D);
    for (int i=1;i<=m;i++){
        char c;
        cin>>c;
        ll x;
        if (c=='A'){  //根据题面的操作，注意细节。
            scanf("%lld",&x);
            a[++n]=(x+t)%D;
            change(n);
        }else{
            int L; scanf("%d",&L);
            ll ans;
            if (L==1){
                printf("%lld\n",a[n]);
                t=a[n]; continue;
            }
            ans=find(n-L+1,n);
            printf("%lld\n",ans); t=ans;
        }
    }
    return 0;
}
