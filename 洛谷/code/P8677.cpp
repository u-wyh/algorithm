// https://www.luogu.com.cn/problem/P8677
// 题意：输入 n、建设需求 B_1..B_n、维护人数 S_1..S_n 和 n-1 条带权无向树边；
// 任选一点建立空运站，从空运站出发沿树边运送设备建好所有油井后返回空运站（边可重复走），建第 i 个油井时当前可用人数须 >= B_i
// 建成后须永久留下 S_i 人维护；
// 输出最短总运输路程以及在总路程最短下的最少初始总人数。
// 数据范围：1 <= n <= 10^5，B_i, S_i 与边权 b（原文误写 c）均为不超过 10000 的正整数。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int n;
int a[MAXN],b[MAXN];

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
    }
    int ans=0;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        ans+=2*v;
        addedge(u,i+1);
        addedge(i+1,u);
    }
    cout<<ans<<' ';
    return 0;
}
