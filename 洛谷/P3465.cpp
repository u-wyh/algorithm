#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m;
int ans[MAXN];
bool vis[MAXN];
bool fanzu;

int head[MAXN];
int to[MAXM<<1];
int Next[MAXM<<1];
int cnt=1;

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

void dfs2(int u,int v){
    if(ans[u]){
        //只有开始设定的根 ans是0
        dfs2(ans[u],u);
    }
    ans[u]=v;
}

void dfs(int u,int f){
    vis[u]=true;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==f){
            continue;//不走重复边
        }
        if(vis[v]){
            //表示出现了返祖现象
            if(!fanzu){
                //如果这个联通块以前没有出现过返祖  那么继续操作
                //否则就不要管
                fanzu=true;
                dfs2(v,u);//返回改变边的方向
            }
        }
        else{
            ans[v]=u;
            dfs(v,u);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            //表示这个联通块未被访问过
            fanzu=false;
            dfs(i,0);
            if(!fanzu){
                //遍历完之后还是没有返祖行为
                cout<<"NIE"<<endl;
                return 0;
            }
        }
    }
    cout<<"TAK"<<endl;
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
