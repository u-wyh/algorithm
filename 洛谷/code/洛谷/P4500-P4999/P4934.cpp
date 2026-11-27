// https://www.luogu.com.cn/problem/P4934
// 题意：给定 n 个互不相同的魔力值 a_i，
// 若 (a_i & a_j) >= min(a_i, a_j) 则两者不能同箱
// 求最少需要多少个箱子装下所有礼物
// （可选输出 0 仅回答最少箱子数拿 60% 分，或输出 1 并给出完整分组方案）
// 。
// 数据范围：20 个测试点中 5 <= n <= 10^6，
// 3 <= k <= 20，0 <= a_i < 2^k。
// 算法标签：状态压缩动态规划、位运算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1<<20;

int n,k;
int f[MAXN];
vector<int>g[21];
bool vis[MAXN];

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
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        int val=read();
        vis[val]=true;
    }
    int maxval=(1<<k)-1;
    for(int i=0;i<=maxval;i++){
        for(int j=i;j;j-=(j&-j)){
            f[i]=max(f[i],f[i-(j&-j)]);
        }
        if(vis[i]){
            f[i]++;
            g[f[i]].push_back(i);
        }
    }
    cout<<1<<endl;
    cout<<f[maxval]<<endl;

    for(int i=1;i<=f[maxval];i++){
        cout<<g[i].size()<<' ';
        for(int j=0;j<(int)g[i].size();j++){
            cout<<g[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}