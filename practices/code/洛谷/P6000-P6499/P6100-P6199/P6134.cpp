// https://www.luogu.com.cn/problem/P6134
// 题意：给定 N 点 M 边的有向无环图（无重边），
// 求在保持原图任意两点可达性不变的前提下，最多能删掉多少条边。
// 数据范围：1 <= N <= 3 * 10^4，0 <= M <= 10^5。
// 难度评分：1800（洛谷分级换算）
// 算法标签：拓扑排序、Bitset
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 1e5+5;

int n,m;

vector<int>vec[MAXN];

int in[MAXN];
queue<int>q;
int topo[MAXN];
bitset<MAXN>bs[MAXN];
int cnt[MAXN];

bool cmp(int a,int b){
    return cnt[a]>cnt[b];
}

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
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back(v);
        in[v]++;
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    int rk=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        topo[++rk]=u;
        for(int i=0;i<(int)vec[u].size();i++){
            int v=vec[u][i];
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    int ans=0;
    for(int i=n;i>=1;i--){
        int u=topo[i];
        bs[u].set(u);
        if(!vec[u].empty()){
            sort(vec[u].begin(),vec[u].end(),cmp);
            for(auto v:vec[u]){
                if(bs[u][v]){
                    ans++;
                }
                else{
                    bs[u]|=bs[v];
                }
            }
        }
        cnt[u]=bs[u].count();
    }
    cout<<ans<<endl;
    return 0;
}