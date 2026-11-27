// https://www.luogu.com.cn/problem/P10729
// 题意：每天买一个大小为 a[i] 的套娃。
// 只有外层大小至少比内层大 2，才能套进去。
// 对每一天，输出用截至当天买到的套娃最多能套多少层。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ a[i] ≤ 500000。
// 算法标签：并查集

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int fa[MAXN],sz[MAXN];
bool vis[MAXN];
int n;
int ans;

int find(int i){
    return fa[i]==i?i:fa[i]=find(fa[i]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

int main()
{
    for(int i=1;i<MAXN;i++){
        fa[i]=i;
        sz[i]=1;
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(vis[x]){
            cout<<ans<<' ';
            continue;
        }
        vis[x]=1;
        if(!vis[x-1]&&!vis[x+1]){
            ans++;
        }
        else if(!vis[x-1]){
            un(x,x+1);
            ans+=sz[find(x)]%2;
        }
        else if(!vis[x+1]){
            un(x,x-1);
            ans+=sz[find(x)]%2;
        }
        else{
            ans-=(sz[find(x-1)]+1)/2;
            ans-=(sz[find(x+1)]+1)/2;
            un(x,x-1);
            un(x,x+1);
            ans+=(sz[find(x)]+1)/2;
        }
        cout<<ans<<' ';
    }
    return 0;
}
