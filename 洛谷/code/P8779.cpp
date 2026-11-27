// https://www.luogu.com.cn/problem/P8779
// 题意：输入 N, M, Q、M 个区间部分和条件 (l_i, r_i, S_i)（即 A_{l_i}+...+A_{r_i} = S_i
// 保证无矛盾）以及 Q 个区间和询问 (l, r)；
// 对每个询问输出区间 [l, r] 的元素和，若无法唯一确定则输出 UNKNOWN。
// 数据范围：1 <= N, M, Q <= 10^5，-10^12 <= S_i <= 10^12，1 <= l_i <= r_i <= N
// 1 <= l <= r <= N。
// 算法标签：带权并查集、前缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+6;
int fa[N],sum[N];
int n,m,q;
int l,r,s;
int find(int x){
    if(fa[x]==x)return x;
    int root=find(fa[x]);
    sum[x]+=sum[fa[x]];
    fa[x]=root;
    return fa[x];
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>l>>r>>s;
        l--;
        int fl=find(l),fr=find(r);
        if(fl!=fr){
            fa[fl]=fr;
            sum[fl]=-s-sum[l]+sum[r];
        }
    }
    for(int i=1;i<=q;i++){
        cin>>l>>r;
        l--;
        int fl=find(l),fr=find(r);
        if(fl!=fr){
            cout<<"UNKNOWN"<<'\n';
            continue;
        }
        cout<<sum[r]-sum[l]<<'\n';
    }
    return 0;
}
