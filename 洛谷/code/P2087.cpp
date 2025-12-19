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