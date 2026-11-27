// https://www.luogu.com.cn/problem/P8779
// 题意：输入 N, M, Q、M 个区间部分和条件 (l_i, r_i, S_i)（即 A_{l_i}+...+A_{r_i} = S_i
// 保证无矛盾）以及 Q 个区间和询问 (l, r)；
// 对每个询问输出区间 [l, r] 的元素和，若无法唯一确定则输出 UNKNOWN。
// 数据范围：1 <= N, M, Q <= 10^5，-10^12 <= S_i <= 10^12，1 <= l_i <= r_i <= N
// 1 <= l <= r <= N。
// 算法标签：带权并查集、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,q;
long long dist[MAXN];
int fa[MAXN];
int sz[MAXN];

void prepare(){
    for(int i=0;i<=n;i++){
        sz[i]=1;
        fa[i]=i;
    }
}

int find(int x){
    if(x!=fa[x]){
        int tmp=fa[x];
        fa[x]=find(tmp);
        dist[x]+=dist[tmp];
    }
    return fa[x];
}

void un(int l,int r,long long v){
    int lf=find(l);
    int rf=find(r);
    if(lf==rf){
        return ;
    }
    if(sz[lf]<sz[rf]){
        fa[lf]=rf;
        sz[rf]+=sz[lf];
        dist[lf]=dist[r]+v-dist[l];
    }
    else{
        fa[rf]=lf;
        sz[lf]+=sz[rf];
        dist[rf]=dist[l]-v-dist[r];
    }
}

void query(int l,int r){
    if(find(l)!=find(r)){
        cout<<"UNKNOWN"<<endl;
        return ;
    }
    cout<<(dist[l]-dist[r])<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    prepare();
    for(int i=1;i<=m;i++){
        int l,r;
        long long v;
        cin>>l>>r>>v;
        r++;
        un(l,r,v);
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        r++;
        query(l,r);
    }
    return 0;
}