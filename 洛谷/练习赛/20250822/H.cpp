#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 150005;
const int MAXM = 32*MAXN;

int n;
int nums[MAXN];

int cnt=1;
int trie[MAXM][2];
int dep[MAXM];

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

void insert(int val){
    int cur=1;
    for(int i=30;i>=0;i--){
        int path=(val>>i)&1;
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
}

void dfs(int u,int d){
    if(d<0){
        return ;
    }
    if(trie[u][0]){
        dfs(trie[u][0],d-1);
    }
    if(trie[u][1]){
        dfs(trie[u][1],d-1);
    }
    if(!trie[u][0]||!trie[u][1]){
        dep[u]=(1ll<<d);
    }
    dep[u]+=max(dep[trie[u][0]],dep[trie[u][1]]);
    // cout<<u<<' '<<d<<' '<<dep[u]<<endl;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        insert(nums[i]);
    }
    dfs(1,30);
    // cout<<dep[1]<<endl;
    int ans=(1ll<<31)-1-dep[1];
    // int cur=1;
    // int ans=0;
    // for(int i=30;i>=0;i--){
    //     if(!trie[cur][0]||!trie[cur][1]){
    //         cur=trie[cur][0]+trie[cur][1];
    //         continue;
    //     }
    //     ans+=(1ll<<i);
    //     if(dep[trie[cur][0]]>dep[trie[cur][1]]){
    //         cur=trie[cur][0];
    //     }
    //     else if(dep[trie[cur][0]]<dep[trie[cur][1]]){
    //         cur=trie[cur][1];
    //     }
    //     else{
    //         ans+=(1ll<<(i+1))-1-dep[trie[cur][0]];
    //         break;
    //     }
    // }
    cout<<ans<<endl;
    return 0;
}