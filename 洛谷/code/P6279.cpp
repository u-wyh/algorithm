#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int cnt;
int fa[MAXN<<1];
int vis[MAXN];

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    if(fx<=n){
        swap(fx,fy);
    }
    fa[fx]=fy;
    if(fx<=n&&fy<=n){
        un(fx+n,fy+n);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n*2;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        un(u+n,v);
    }
    for(int i=1;i<=n;i++){
        int f=find(i);
        if(vis[f]){
            cout<<vis[f]<<endl;
        }
        else{
            vis[f]=++cnt;
            cout<<cnt<<endl;
        }
    }
    return 0;
}