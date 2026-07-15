//P2863
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

