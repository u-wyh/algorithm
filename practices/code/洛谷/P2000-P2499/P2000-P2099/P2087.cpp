// https://www.luogu.com.cn/problem/P2087
// 题意：有 n 个人和 m 个房间，初始所有人都在 1 号房间，共 q 次操作。
// C i j：让第 i 个人去房间 j。
// W l r：让闭区间 [l,r] 的房间做实验，获得房间内人数的点数。
// 若这整群人（同一个人员集合，不限房间）此前已一起做过实验，则本次不增加点数。
// 按顺序输出每次 W 操作获得的点数。
// 数据范围：n, m, q <= 10^5。
// 算法标签：异或哈希、有序集合
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,q;
map<long long,bool>hashmap;
set<int>active;
long long h[MAXN];
long long val[MAXN];
int sz[MAXN];
int belong[MAXN];

mt19937_64 rng(time(0));

int main()
{
    srand(200512);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        val[i] = rng();
        h[1]^=val[i];
        belong[i]=1;
    }
    active.insert(1);
    sz[1]=n;
    while(q--){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='C'){
            if(belong[x]==y){
                continue;
            }
            active.erase(belong[x]);
            active.erase(y);

            h[belong[x]]^=val[x];
            sz[belong[x]]--;

            if(!hashmap[h[belong[x]]]){
                active.insert(belong[x]);
            }

            belong[x]=y;
            h[y]^=val[x];
            sz[y]++;

            if(!hashmap[h[y]]){
                active.insert(y);
            }
        }
        else{
            int ans=0;
            auto it=active.lower_bound(x);
            while(it!=active.end()&&*it<=y){
                ans+=sz[*it];
                hashmap[h[*it]]=1;
                it=active.erase(it);
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
/*

3 5 7
C 1 2
C 2 2
W 1 2
C 3 2
W 1 2
C 3 3
W 1 3
*/