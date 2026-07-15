#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int n,m;
int fa[MAXN];
int dist[MAXN];
int val[MAXN];

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

int find(int i){
    if(i!=fa[i]){
        int tmp=fa[i];
        fa[i]=find(fa[i]);
        dist[i]+=dist[tmp];
    }
    return fa[i];
}

void un(int l,int r){
    int lf=find(l),rf=find(r);
    if(lf!=rf){
        fa[lf]=rf;
        dist[lf]=val[lf]-val[rf];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            un(u,v);
        }
        else{
            u=find(u);
            val[u]+=v;
        }
    }
    for(int i=1;i<=n;i++){
        int fa=find(i);
        printf("%d ",val[fa]+dist[i]);
    }
    return 0;
}