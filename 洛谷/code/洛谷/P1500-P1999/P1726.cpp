// https://www.luogu.com.cn/problem/P1726
// 题意：给定 N 个村庄及 M 条道路，t=1 表示从 a 到 b，
// t=2 表示双向。
// 找出人数最多的一组两两可以互相到达的村庄，输出数量和升序编号，
// 并列时选编号序列字典序最小的一组。
// 数据范围：1 ≤ N ≤ 5000，0 ≤ M ≤ 50000，
// 村庄编号在 [1,N]，道路不重复。

//P2863
// 算法标签：Tarjan、强连通分量
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
vector<int>col[MAXN];
int sz[MAXN];
bool instack[MAXN];
int n,m;
vector<int>ans;

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        ++color;
        sz[color]++;
        col[color].push_back(x);
        while(st[top]!=x){
            col[color].push_back(st[top]);
            sz[color]++;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,op;
        cin>>u>>v>>op;
        vec[u].push_back(v);
        if(op==2)
            vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    int k=0;
    for(int i=1;i<=color;i++){
        if(sz[i]>k){
            k=sz[i];
        }
    }
    for(int i=1;i<=color;i++){
        if(sz[i]==k){
            ans.push_back(i);
        }
    }
    int tmp=INT_MAX,temp;
    for(int i=0;i<ans.size();i++){
        int v=ans[i];
        sort(col[v].begin(),col[v].end());
        if(col[v][0]<tmp){
            tmp=col[v][0];
            temp=v;
        }
    }
    cout<<k<<endl;
    for(int i=0;i<k;i++){
        cout<<col[temp][i]<<' ';
    }
    return 0;
}

