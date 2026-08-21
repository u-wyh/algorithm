#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,m;
int edge;
int ans;

string str[MAXN];

int cnt=1;
int tree[MAXN][26];

int cntn;
int tim[MAXN];
int dep[MAXN];

int to[MAXN];

// 下一次的时间点
int nxt[MAXN];
// 树上节点目前对应的节点
int now[MAXN];
int bel[MAXN];

bool in[MAXN];

struct compare{
    bool operator()(const int &a,const int &b){
        if(nxt[a]!=nxt[b]){
            return nxt[a]<nxt[b];
        }
        return dep[a]<dep[b];
    }
};
priority_queue<int,vector<int>,compare>heap;

void insert(string word){
    int cur=1;
    for (char ch : word){
        int path=ch-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
}

void insert2(string word,int t){
    int cur=1;
    int d=0;
    for (char ch : word){
        d++;
        int path=ch-'a';
        cur=tree[cur][path];

        cntn++;
        bel[cntn]=cur;
        nxt[cntn]=(now[cur]==0)?MAXN:tim[now[cur]];
        to[cntn]=now[cur];
        tim[cntn]=t;
        dep[cntn]=d;
        now[cur]=cntn;
    }
}

void add(int x){
    if(x==0){
        return ;
    }
    in[x]=true;
    heap.push(x);
}

void insert3(string word){
    int cur=1;
    for (char ch : word){
        int path=ch-'a';
        cur=tree[cur][path];

        if(!in[now[cur]]){
            add(now[cur]);
            edge++;
            ans++;
        }
        else{
            in[now[cur]]=false;
            now[cur]=to[now[cur]];
            add(now[cur]);
        }
    }
}

void compute(){
    while(edge>m){
        int u=heap.top();
        // cout<<u<<endl;
        heap.pop();
        if(!in[u]){
            continue;
        }
        edge--;
        now[bel[u]]=to[u];
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        insert(str[i]);
    }

    cntn=cnt;
    for(int i=n;i>=1;i--){
        insert2(str[i],i);
    }

    for(int i=1;i<=n;i++){
        insert3(str[i]);
        compute();
    }
    cout<<ans<<endl;
    return 0;
}