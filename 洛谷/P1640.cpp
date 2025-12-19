#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 1e4+5;

int n;
int fa[MAXM];
int edge[MAXM];

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
    if(fx!=fy){
        fa[fy]=fx;
        edge[fx]+=edge[fy]+1;
    }
    else{
        edge[fx]+=1;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=10000;i++){
        fa[i]=i;
        edge[i]=0;
    }
    for(int i=1;i<=n;i++){
        int u,v;
        u=read(),v=read();
        un(u,v);
    }
    for(int i=1;i<=10001;i++){
        int f=find(i);
        if(edge[f]>=1){
            edge[f]--;
            continue;
        }
        else{
            cout<<(i-1)<<endl;
            return 0;
        }
    }
    return 0;
}