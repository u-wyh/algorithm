// https://www.luogu.com.cn/problem/P3472
// 题意：输入黑帮成员数 n（1..n），以及每个人瞄准的目标编号 s_1..s_n（允许 s_i = i）。
// 成员按某种未知顺序依次开枪：每人最多开一枪，若开枪前已被打死则不能再开枪；目标立即死亡且开枪者不会更换目标。
// 输出一行两个整数，分别表示所有可能开枪顺序下最少死亡人数和最多死亡人数。
// 数据范围：1 <= n <= 1000000，1 <= s_i <= n。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;

int minans,maxans;

int in[MAXN];
queue<int>q;
bool strive[MAXN];
bool die[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
bool instack[MAXN];
int top;
int color;
int col[MAXN];
int sz[MAXN];
int degree[MAXN];
bool flag[MAXN];

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

void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt;
    instack[u] = true;
    st[++top] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        col[u]=++color;
        sz[color]++;
        instack[u]=false;
        while(st[top]!=u){
            int v=st[top];
            instack[v]=false;
            col[v]=color;
            sz[color]++;
            top--;
        }
        top--;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int u=read();
        addedge(i,u);
        in[u]++;
    }

    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
            strive[i]=true;
            minans++;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(die[v]){
                continue;
            }
            die[v]=true;
            for(int ei=head[v];ei;ei=nxt[ei]){
                int t=to[ei];
                in[t]--;
                if(in[t]==0){
                    strive[i]=true;
                    q.push(t);
                    minans++;
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int u=1;u<=n;u++){
        if(die[u]||strive[u]){
            flag[col[u]]=true;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(col[u]!=col[v]){
                degree[col[v]]++;
            }
        }
    }
    for(int i=1;i<=color;i++){
        if(degree[i]==0){
            maxans++;
        }
        if(!flag[i]){
            minans+=sz[i]/2;
        }
    }
    minans=n-minans;
    maxans=n-maxans;
    cout<<minans<<' '<<maxans<<endl;
    return 0;
}