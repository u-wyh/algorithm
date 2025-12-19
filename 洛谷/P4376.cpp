#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 5e4+5;

vector<int>vec[MAXN];
int x;
int n,m;

bool vis[MAXN];
int t[MAXN];
int in[MAXN];

int head[MAXN];
int to[MAXN<<1];
int Next[MAXN<<1];
int cnt=1;

priority_queue<int, vector<int>, greater<int>> heap;

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool dfs(int u){
    t[u]++;
    if(t[u]>n){
        return false;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(vis[v]){
            continue;
        }
        else{
            if(!dfs(v)){
                return false;
            }
        }
    }
    vis[u]=true;
    return true;
}

bool check(int x){
    for(int i=1;i<=n;i++){
        head[i]=0;
        vis[i]=false;
        t[i]=0;
    }
    cnt=1;
    for(int i=1;i<=x;i++){
        for(int j=1;j<vec[i][0];j++){
            //cout<<i<<' '<<vec[i][j]<<' '<<vec[i][j+1]<<endl;
            addedge(vec[i][j],vec[i][j+1]);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            if(!dfs(i)){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read();
        vec[i].push_back(u);
        vec[i].resize(u+1);
        for(int j=1;j<=u;j++){
            vec[i][j]=read();
        }
    }
    int l=1,r=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            x=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
    cnt=1;
    for(int i=1;i<=x;i++){
        for(int j=1;j<vec[i][0];j++){
            addedge(vec[i][j],vec[i][j+1]);
            in[vec[i][j+1]]++;
        }
    }
    //cout<<cnt<<endl;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            heap.push(i);
        }
    }
    while(!heap.empty()){
        int u=heap.top();
        heap.pop();
        cout<<u<<' ';
        for(int i=head[u];i;i=Next[i]){
            in[to[i]]--;
            if(in[to[i]]==0){
                heap.push(to[i]);
            }
        }
    }
    return 0;
}
