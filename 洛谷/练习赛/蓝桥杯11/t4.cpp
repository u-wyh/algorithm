#include<bits/stdc++.h>
using namespace std;

bool ok[128];
int ans=0;
int ct[128];

int cnt,res;
int fa[7];
bool vis[7];
bool visit[7];

int tot=1;
int head[7];
int nxt[100];
int to[100];

void addedge(int u,int v){
    u--,v--;
    nxt[tot]=head[u];
    to[tot]=v;
    head[u]=tot++;
}

void dfs(int u){
    visit[u]=1;
    res++;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(visit[v]){
            continue;
        }
        if(vis[v]){
            dfs(v);
        }
    }
}

bool check(int st){
    cnt=0;
    for(int i=0;i<7;i++){
        vis[i]=false;
        visit[i]=false;
        if(st&(1<<i)){
            cnt++;
            vis[i]=true;
        }
    }
    for(int i=0;i<6;i++){
        if(vis[i]){
            res=0;
            dfs(i);
            break;
        }
    }
    return cnt==res;
}

int main()
{
    addedge(1,2);
    addedge(2,1);
    addedge(1,3);
    addedge(3,1);
    addedge(2,4);
    addedge(4,2);
    addedge(2,5);
    addedge(5,2);
    addedge(3,4);
    addedge(4,3);
    addedge(4,5);
    addedge(5,4);
    addedge(4,6);
    addedge(6,4);
    addedge(5,7);
    addedge(7,5);
    addedge(6,7);
    addedge(7,6);
    int ans=0;
    for(int i=1;i<=127;i++){
        if(check(i)){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}