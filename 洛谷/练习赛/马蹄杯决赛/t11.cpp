#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;
const int MOD = 998244353;

int n;
int ans;
string s;
int cnt=1;
int tree[MAXN][26];
int pass[MAXN];
int en[MAXN];

void insert(string s){
    int cur=1;
    pass[cur]++;

    int len=s.length();
    // ans=(ans+len)%MOD;
    for(int i=0;i<len;i++){
        int path=s[i]-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
        pass[cur]++;
    }
    en[cur]++;
}

void bfs(){
    queue<pair<int,int>>q;
    q.push({1,0});
    while(!q.empty()){
        int u=q.front().first;
        int d=q.front().second;
        q.pop();
        ans=(ans+(((pass[u]-en[u])*en[u])%MOD*d)%MOD)%MOD;
        ans=(ans+((en[u]*en[u])%MOD*d)%MOD)%MOD;
        for(int i=0;i<26;i++){
            if(tree[u][i]){
                ans=(ans+(((pass[u]-pass[tree[u][i]])*pass[tree[u][i]])%MOD*d)%MOD)%MOD;
                q.push({tree[u][i],d+1});
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    // dfs(1,0);
    bfs();
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}