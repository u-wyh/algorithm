//P3520
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m;
int degree[MAXN];
bool visit[MAXN];

int tot=0;//环的个数
vector<int>ans[MAXM];//记录答案

stack<int>st;
bool in[MAXM];//是否在栈中

int cnt=0;
int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int vis[MAXM<<1];

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

void dfs(int u){
    visit[u]=true;
    for(int i=head[u];i!=-1;i=Next[i]){
        if(!vis[i]){
            vis[i]=vis[i^1]=true;
            head[u]=Next[i];//相当于是把当前的head[u]这条边删除了
            int v=to[i];
            dfs(v);
        }
    }
    if(in[u]){
        ans[++tot].push_back(u);
        while(st.top()!=u){
            ans[tot].push_back(st.top());
            in[st.top()]=false;
            st.pop();
        }
        ans[tot].push_back(u);
    }
    else{
        st.push(u);
        in[u]=true;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        head[i]=-1;
    }
    for(int i=1;i<=m;i++){
        int u,v,s,t;
        u=read(),v=read(),s=read(),t=read();
        if(s^t){
            addedge(u,v);
            addedge(v,u);
            degree[u]++,degree[v]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(degree[i]&1){
            cout<<"NIE"<<endl;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(!visit[i]){
            dfs(i);
        }
    }
    cout<<tot<<endl;
    for(int i=1;i<=tot;i++){
        cout<<(ans[i].size()-1)<<' ';
        for(int j=0;j<ans[i].size();j++){
            cout<<ans[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
