#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 5e4+5;

int n,m;
int degree[MAXN];
int cnt=0;
int vis[MAXM<<1];
vector<pair<int,int>>vec[MAXN];
stack<int>st;
int fa[MAXN];

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

void dfs(int u){
    for(int i=0;i<vec[u].size();i++){
        if(!vis[vec[u][i].second]){
            vis[vec[u][i].second]=true;
            dfs(vec[u][i].first);
        }
    }
    st.push(u);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back({v,cnt++});
        vec[v].push_back({u,cnt++});
        degree[u]++,degree[v]++;
    }
    dfs(1);
    while(!st.empty()){
        int u=st.top();
        cout<<u<<endl;
        st.pop();
    }
    return 0;
}
