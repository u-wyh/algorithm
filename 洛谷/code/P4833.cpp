#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e6+5;

int n,m;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

set<int>unvisited;
vector<int>sz;

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

void compute(int st){
    queue<int>q;
    q.push(st);
    int size=0;
    unvisited.erase(st);

    while(!q.empty()){
        int u=q.front();
        q.pop();
        size++;

        set<int>neighbor;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            neighbor.insert(v);
        }
        vector<int>vec;
        for(int v:unvisited){
            if(!neighbor.count(v)){
                vec.push_back(v);
            }
        }
        for(int i=0;i<(int)vec.size();i++){
            unvisited.erase(vec[i]);
            q.push(vec[i]);
        }
    }
    sz.push_back(size);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        unvisited.insert(i);
    }

    while(!unvisited.empty()){
        int u=*unvisited.begin();
        compute(u);
    }

    cout<<sz.size()<<endl;
    sort(sz.begin(),sz.end());
    for(int i=0;i<(int)sz.size();i++){
        cout<<sz[i]<<' ';
    }
    return 0;
}