// https://www.luogu.com.cn/problem/P8819
// 题意：输入 n 个据点和 m 条单向虫洞 (u, v)（无重边自环，初始全可用）
// 再输入 q 次操作并每次询问当前是否所有据点都既能无限次沿可用虫洞穿梭、又满足
// 恰好只有 1 条出边可用（能则输出 YES，否则 NO）；
// 操作为：1 u v 摧毁边 (u, v)，2 u 摧毁指向 u 的所有可用虫洞，
// 3 u v 修复边 (u, v)，4 u 修复指向 u 的所有被摧毁虫洞。
// 数据范围：1 <= n, m, q <= 5*10^5。
// 算法标签：随机化、哈希
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,m,q;

int val[MAXN];
int allsum[MAXN];
int cursum[MAXN];
int sum;
int target;

mt19937_64 rng(time(0));

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        val[i]=rng();
        target+=val[i];
    }

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        allsum[v]+=val[u];
    }
    for(int i=1;i<=n;i++){
        cursum[i]=allsum[i];
        sum+=cursum[i];
    }

    cin>>q;
    for(int i=1;i<=q;i++){
        int op,u,v;
        cin>>op;
        if(op==1){
            cin>>u>>v;
            cursum[v]-=val[u];
            sum-=val[u];
        }
        else if(op==2){
            cin>>v;
            sum-=cursum[v];
            cursum[v]=0;
        }
        else if(op==3){
            cin>>u>>v;
            cursum[v]+=val[u];
            sum+=val[u];
        }
        else{
            cin>>v;
            sum-=cursum[v];
            cursum[v]=allsum[v];
            sum+=cursum[v];
        }

        if(sum==target){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}