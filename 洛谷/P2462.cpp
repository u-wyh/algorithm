#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e4+5;
const int MAXM = 105;
const int ALPHA = 27;
const int BASE = 499;
const int MAXE = MAXN * 100;

int p[ALPHA];

int n;
struct word{
    char s[MAXM];
    int len;
    int freq[ALPHA];
    // int id;
    int val;
};
word words[MAXN];
map<int,int>mp;
vector<int>vec[MAXN];
int id;

int head[MAXN];
int nxt[MAXE];
int to[MAXE];
int cnt=1;

int in[MAXN];
int dp[MAXN];
int fa[MAXN];

inline void addedge(int u,int v){
    // cout<<u<<' '<<v<<endl;
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
    in[v]++;
}

void topo(){
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            dp[i]=1;
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dp[v]<dp[u]+1){
                fa[v]=u;
                dp[v]=dp[u]+1;
            }
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
}

void traceback(int id){
    if(id==0){
        return ;
    }
    traceback(fa[id]);
    cout<<(words[id].s+1)<<endl;
}

signed main()
{
    p[0]=1;
    for(int i=1;i<=26;i++){
        p[i]=p[i-1]*BASE%MOD;
    }

    n=1;
    while(scanf("%s",words[n].s+1)!=EOF){
        words[n].len=strlen(words[n].s+1);
        // words[n].id=n;
        for(int i=1;i<=words[n].len;i++){
            words[n].freq[words[n].s[i]-'a'+1]++;
        }
        int val=0;
        for(int i=1;i<=26;i++){
            val=(val+words[n].freq[i]*p[i])%MOD;
        }
        words[n].val=val;
        if(mp[val]){
            vec[mp[val]].push_back(n);
        }
        else{
            mp[val]=++id;
            vec[id].push_back(n);
        }
        n++;
    }
    n--;
    for(int i=1;i<=n;i++){
        int val=words[i].val;
        for(int j=1;j<=26;j++){
            int newval=(val+p[j])%MOD;
            int hid=mp[newval];
            if(hid){
                for(int k=0;k<(int)vec[hid].size();k++){
                    addedge(i,vec[hid][k]);
                }
            }
        }
    }
    topo();
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        if(dp[i]>ans2){
            ans1=i;
            ans2=dp[i];
        }
    }
    cout<<ans2<<endl;
    traceback(ans1);
    return 0;
}