// https://www.luogu.com.cn/problem/P2444
//这道题主要考察的就是AC自动机是一个完备状态自动机  即所有的状态一定存在于自动机上
//这里的状态一定是某个节点的状态  如果对应的是一个单词的话  那么就是这个单词最后一个节点的状态
//所以对于这道题而言 只要有安全状态形成了环  那么一定可以无限循环  否则一定会有终结的哪一个位置
//在这里使用拓扑排序来判断是否存在环
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;

int n;
string s;

int tree[MAXN][2];
int fail[MAXN];
bool en[MAXN];
int cnt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int in[MAXN];
bool vis[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void insert(string s){
    int cur=0;
    for(char ch:s){
        int path=ch-'0';
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
    }
    en[cur]=true;
}

void setfail(){
    queue<int>q;
    for(int i=0;i<2;i++){
        if(tree[0][i]){
            q.push(tree[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<2;i++){
            if(tree[u][i]==0){
                tree[u][i]=tree[fail[u]][i];
            }
            else{
                fail[tree[u][i]]=tree[fail[u]][i];
                q.push(tree[u][i]);
            }
        }
        en[u]=en[u]||en[fail[u]];
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    setfail();
    queue<int>q;
    int ans=1;
    q.push(0);
    vis[0]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<2;i++){
            int v=tree[u][i];
            if(en[v]){
                continue;
            }
            addedge(u,v);
            in[v]++;
            if(!vis[v]){
                q.push(v);
                vis[v]=true;
                ans++;
            }
        }
    }
    int res=0;
    for(int i=0;i<=cnt;i++){
        if(vis[i]&&in[i]==0){
            q.push(i);
            res++;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            in[v]--;
            if(in[v]==0){
                res++;
                q.push(v);
            }
        }
    }
    if(ans==res){
        cout<<"NIE"<<endl;
    }
    else{
        cout<<"TAK"<<endl;
    }
    return 0;
}