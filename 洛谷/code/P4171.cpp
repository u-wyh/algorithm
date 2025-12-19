#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 2005;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];

void init(){
    cnt=1;
    top=0;
    color=0;
    Time=0;
    for(int i=0;i<=2*n;i++){
        dfn[i]=0;
        low[i]=0;
        col[i]=0;
        head[i]=0;
    }
}

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        //12  34  56  78
        init();
        for(int i=1;i<=m;i++){
            char c1,c2;
            int u,v;
            cin>>c1>>u>>c2>>v;
            //cout<<u<<' '<<v;
            u=2*(u-1),v=2*(v-1);
            u+=(c1=='m')?2:1;
            v+=(c2=='m')?2:1;
            //cout<<' '<<u<<' '<<v<<endl;
            addedge((v%2)?(v+1):(v-1),u);
            addedge((u%2)?(u+1):(u-1),v);
        }
        for(int i=1;i<=2*n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        bool flag=true;
        for(int i=1;i<=2*n;i+=2){
            if(col[i]==col[i+1]){
                flag=false;
                cout<<"BAD"<<endl;
                break;
            }
        }
        if(flag){
            cout<<"GOOD"<<endl;
        }
    }
    return 0;
}
