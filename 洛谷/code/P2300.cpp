// https://www.luogu.com.cn/problem/P2300
// 题意：给定长度为 n 的正整数序列 p，每次可将某数合并到相邻数上（值相加，长度减 1）。
// 求将序列合并为从左到右单调不减的最少合并次数。
// 输出最少合并次数。
// 数据范围：0 < n <= 2*10^5，0 < p_i <= 2147483647，p 随机生成。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[MAXN];
long long sum[MAXN];

int f[MAXN];
long long g[MAXN];

int head,tail;
int que[MAXN];

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
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+val[i];
    }
    head=1,tail=0;
    que[++tail]=0;
    for(int i=1;i<=n;i++){
        while(head+1<=tail&&sum[i]>=sum[que[head+1]]+g[que[head+1]]){
            head++;
        }
        f[i]=f[que[head]]+i-que[head]-1;
        g[i]=sum[i]-sum[que[head]];
        while(head<=tail&&((sum[que[tail]]+g[que[tail]])>=(sum[i]+g[i]))){
            tail--;
        }
        que[++tail]=i;
    }
    cout<<f[n]<<endl;
    return 0;
}