// https://codeforces.com/problemset/problem/1998/E1
// 题意：每组给 n 个球的初始权值和参数 x。
// 独立考虑每个长度从 x 到 n 的前缀。
// 每次选当前相邻两球，权值较大者吞掉较小者，
// 相等时任选一球吞掉另一球，两球权值相加。
// 重复直到只剩一球，统计哪些球可能最后留下。
// 输出：每组输出整个序列最后可能留下的球的个数。
// 数据范围：1 <= t <= 10^4，1 <= n <= 2*10^5，
// x = n，1 <= a_i <= 10^9。
// 所有组的 n 之和不超过 2*10^5。
// 难度评分：2200（CF 官方）
// 算法标签：笛卡尔树、并查集、单调栈
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,x;
long long val[MAXN];
long long sum[MAXN];
int ls[MAXN];
int rs[MAXN];
int top;
int st[MAXN];
int f[MAXN];

int fa[MAXN];
long long all[MAXN];
int sz[MAXN];
int ans[MAXN];

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void build(){
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;
        while(pos&&val[st[pos]]<val[i]){
            pos--;
        }
        if(pos>0){
            rs[st[pos]]=i;
            f[i]=st[pos];
        }
        if(pos<top){
            ls[i]=st[pos+1];
            f[ls[i]]=i;
        }

        st[++pos]=i;
        top=pos;

        if(ls[i]){
            int father=find(ls[i]);
            if(father!=ls[i]){
                fa[i]=father;
                sz[father]++;
            }
            else{
                if(sum[i-1]-sum[st[top-1]]>=val[i]){
                    fa[father]=i;
                    sz[i]+=sz[father];
                }
            }
            all[i]=sum[i-1]-sum[st[top-1]];
        }

        int u=find(i);
        while(u!=st[1]){
            int v=f[u];
            all[u]+=val[i];
            if(all[u]>=val[v]){
                int fx=find(v);
                fa[u]=fx;
                sz[fx]+=sz[u];
            }
            u=find(v);
        }
        ans[i]=sz[find(st[1])];
    }
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":  "<<f[i]<<' '<<ls[i]<<' '<<rs[i]<<endl;
    // }
}

int main()
{
    int T=read();
    while(T--){
        n=read(),x=read();
        for(int i=1;i<=n;i++){
            val[i]=read();
            sum[i]=sum[i-1]+val[i];
        }
        for(int i=1;i<=n;i++){
            f[i]=0;
            all[i]=0;
            fa[i]=i;
            sz[i]=1;
            ls[i]=0;
            rs[i]=0;
        }
        build();
        for(int i=x;i<=n;i++){
            printf("%d ",ans[i]);
        }
        cout<<endl;
    }
    return 0;
}