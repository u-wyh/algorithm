#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
#define int long long
#define HEAP __gnu_pbds::priority_queue<int, cmp, __gnu_pbds::pairing_heap_tag>
const int MAXN = 3e5+5;
const int INF = 2e18;

int n,m;
int val[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int least[MAXN];
int profit[MAXN];

struct cmp{
    bool operator () (int x, int y) {
        return least[x] > least[y];
    }
};
HEAP hp[MAXN];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void compute(int u){
    int now = 0;
    least[u] = 0;
    hp[u].push(u);
    
    while(!hp[u].empty()){
        int cur = hp[u].top();
        hp[u].pop();
        
        if(least[cur] == INF){
            break;
        }
        
        if(now < least[cur]){
            least[u] += least[cur] - now;
            now = least[cur];
        }
        
        if(cur == u){
            now += val[cur];
            for(int i = head[cur]; i; i = nxt[i]){
                int v = to[i];
                hp[u].push(v);
            }
        } else {
            now += profit[cur];
            
            if(hp[u].size() < hp[cur].size()){
                hp[u].swap(hp[cur]);
            }
            
            hp[u].join(hp[cur]);
        }
        
        if(now > least[u]){
            profit[u] = now - least[u];
            return;
        }
    }
    
    least[u] = INF;
}

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    compute(u);
}

// struct compare{
//     bool operator()(const int a,const int b){
//         return least[a]>least[b];
//     }
// };
priority_queue<int,vector<int>,cmp>heap;

int compute(){
    int now=m;
    heap.push(1);
    while(!heap.empty()){
        int u=heap.top();
        heap.pop();

        if(now<least[u]){
            break;
        }
        now+=val[u];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            heap.push(v);
        }
    }
    return now-m;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int fa;
        val[i+1]=read(),fa=read()+1;
        addedge(fa,i+1);
    }
    dfs(1);
    cout<<compute()<<endl;
    return 0;
}