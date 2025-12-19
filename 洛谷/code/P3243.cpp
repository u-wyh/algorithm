//这个不对 求的是字典序最小的情况
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
bool vis[MAXN];
int tot[MAXN];
int in[MAXN];

int head[MAXN];
int to[MAXN];
int Next[MAXN];
int cnt=1;

struct node{
    int sub,minn;
}nums[MAXN];

struct cmp {
    bool operator()(const node& a, const node& b) const {
        //return a.minn==b.minn?(a.t==b.t?(a.sub>b.sub):a.t>b.t):a.minn>b.minn;
        return a.minn==b.minn?a.sub>b.sub:a.minn>b.minn;
    }
};
priority_queue<node, vector<node>, cmp> heap;

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

void build(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        nums[i].sub=i;
        vis[i]=0;
        in[i]=0;
    }
}

inline void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool dfs(int u){
    int flag=1;
    nums[u].minn=u;
    tot[u]++;
    if(tot[u]>n){
        return false;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(vis[v]){
            //表示访问过了
            if(nums[u].minn>nums[v].minn){
                nums[u].minn=nums[v].minn;
            }
            continue;
        }
        if(!dfs(v)){
            flag=0;
            break;
        }
        if(nums[u].minn>nums[v].minn){
            nums[u].minn=nums[v].minn;
        }
    }
    if(!flag){
        return false;
    }
    vis[u]=true;
    return true;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        n=read(),m=read();
        build();
        for(int i=1;i<=m;i++){
            int u,v;
            u=read(),v=read();
            addedge(u,v);
            in[v]++;
        }
        bool flag=1;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                if(!dfs(i)){
                    flag=0;
                    break;
                }
            }
        }
        if(!flag){
            cout<<"Impossible!"<<endl;
            continue;
        }
//        cout<<endl;
//        for(int i=1;i<=n;i++){
//            cout<<i<<": "<<nums[i].minn<<' '<<nums[i].t<<' '<<in[i]<<endl;
//        }
//        cout<<endl;
        for(int i=1;i<=n;i++){
            if(in[i]==0){
                heap.push(nums[i]);
            }
        }
        while(!heap.empty()){
            node u=heap.top();
            heap.pop();
            cout<<u.sub<<' ';
            for(int i=head[u.sub];i;i=Next[i]){
                in[to[i]]--;
                if(!in[to[i]]){
                    heap.push(nums[to[i]]);
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
