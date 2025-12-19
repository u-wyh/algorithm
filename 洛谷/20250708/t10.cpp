#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int maxmex[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

struct cmp{
    bool operator()(int a,int b){
        return a>b;//小根堆
    }
};

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

void prepare(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
}

void dfs(int u,int fa){
    maxmex[u]=0;
    priority_queue<int,vector<int>,cmp>heap;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        heap.push(maxmex[v]);
    }
    while(!heap.empty()){
        int v=heap.top();
        heap.pop();
        if(v>=maxmex[u]){
            maxmex[u]++;
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        n=read();
        prepare();
        for(int i=1;i<n;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,0);
        long long ans=0;
        for(int i=1;i<=n;i++){
            ans+=maxmex[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}