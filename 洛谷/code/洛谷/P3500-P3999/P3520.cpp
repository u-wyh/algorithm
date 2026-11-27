// https://www.luogu.com.cn/problem/P3520
// 题意：输入点数 n、边数 m，
// 以及 m 条无向边各自的端点 a, b、初始状态 s 和目标状态
// t（0 表示清洁，1 表示不清洁）。
// 安排若干辆垃圾车各自沿一条除起点外不重复经过同一点的环路行驶，
// 每次经过会翻转边的状态，且所有卡车经过的总边数不超过 5m。
// 若无解输出 NIE；
// 否则输出环路数量 k 及每条环路经过的边数 k_i 和
// 依次经过的 k_i+1 个顶点编号。
// 数据范围：1 <= n <= 10^5，1 <= m <= 10^6，
// 1 <= a <= b <= n，s, t in {0, 1}。
//P3520
// 算法标签：欧拉回路、深度优先搜索、栈
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
