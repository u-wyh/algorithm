// https://www.luogu.com.cn/problem/P3422
// 题意：输入环形公路上顺时针排列的空间站数量 n，
// 以及每个空间站的补给油量 p_i 和到下一站的距离
// d_i（第 n 站到第 1 站距离为 d_n）。
// 每升油可行驶 1 米，油箱容量无限，
// 从某站出发可选择顺时针或逆时针绕行一圈并回到起点，途中油量不能为负。
// 分别判断从 1..n 号空间站出发能否顺利绕圈回到起点，输出 n 行，
// 可行输出 TAK，否则输出 NIE。
// 数据范围：
// 3 <= n <= 10^6，p_i >= 0，d_i > 0，
// sum(d_i), sum(p_i) <= 2*10^9。
// 算法标签：单调队列、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int p[MAXN];
int d[MAXN];

int sum[MAXN<<1];

bool ans[MAXN];

int q[MAXN];

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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        p[i]=read(),d[i]=read();
    }

    for(int i=1;i<=n;i++){
        sum[i]=sum[i+n]=p[i]-d[i];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]+=sum[i-1];
    }
    
    int head=0,tail=0;
    for(int i=2*n;i>=1;i--){
        while(head<tail&&q[head]>=i+n){
            head++;
        }
        while(head<tail&&sum[q[tail-1]]>=sum[i]){
            tail--;
        }
        q[tail++]=i;
        if(i<=n){
            if(sum[q[head]]-sum[i-1]>=0){
                ans[i]=true;
            }
        }
    }

    d[0]=d[n];
    for(int i=1;i<=n;i++){
        sum[i]=sum[i+n]=p[i]-d[i-1];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]+=sum[i-1];
    }
    head=tail=0;
    for(int i=1;i<=2*n;i++){
        while(head<tail&&q[head]<=i-n-1){
            head++;
        }
        if(i>n){
            if(sum[i]-sum[q[head]]>=0){
                ans[i-n]=true;
            }
        }
        while(head<tail&&sum[q[tail-1]]<=sum[i]){
            tail--;
        }
        q[tail++]=i;
    }
    for(int i=1;i<=n;i++){
        if(ans[i]){
            printf("TAK\n");
        }
        else{
            printf("NIE\n");
        }
    }
    return 0;
}