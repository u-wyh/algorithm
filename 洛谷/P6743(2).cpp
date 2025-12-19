#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int n,m;
bool vis[MAXN<<1];//表示这条边是否经过
bool in[MAXN];
int st[MAXN],r=0;

//这道题的关键就是如何给边编号
//因为这对应着如何标记访问过的边
//vis[i]=vis[i^1]=true   这要求编号从2开始  23 45 67 89
void addedge(int u,int v){
    Next[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}

void dfs(int u){
    for(int i=head[u];i>0;i=head[u]){
        head[u]=Next[i];
        if(vis[i]){
            //表示这条边访问过了  不能再走了
            continue;
        }
        vis[i]=vis[i^1]=true;
        //将正边 反边全部变为1
        dfs(to[i]);
    }
    if(in[u]){
        //表示已经成为了一个环  那么输出这个环
        //并且u一定是起点
        while(st[r]!=u&&r){
            in[st[r]]=false;//表示已经被弹出
            cout<<st[r--]<<' ';
        }
        cout<<st[r--]<<endl;//表示该环上所有的全部弹出
    }
    else in[u]=true;
    st[++r]=u;
    //如果只是一个普通的点 那么直接加入栈
    //即使是经历了上面的判断  那么就会作为新环的起点再次开始
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1);
    return 0;
}
