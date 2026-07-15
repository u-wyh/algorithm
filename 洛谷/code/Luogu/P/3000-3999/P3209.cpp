#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 1e4+5;

int n,m;

int x[MAXM];
int y[MAXM];
bool vis[MAXM];
int id[MAXN];

int fa[MAXM<<1];

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

bool cross(int x1,int y1,int x2,int y2){
    if (x1 < x2 && x2 < y1 && y1 < y2) {
        return true;
    }
    if (x2 < x1 && x1 < y2 && y2 < y1) {
        return true;
    }
    return false;
}

void un(int x,int y){
    fa[x]=y;
}

bool compute(){
    for(int i=1;i<=m;i++){
        if(vis[i]){
            continue;
        }
        for(int j=i+1;j<=m;j++){
            if(vis[j]){
                continue;
            }
            if(!cross(x[i],y[i],x[j],y[j])){
                continue;
            }

            int fx=find(i);
            int fy=find(j);

            if(fx==fy){
                return false;
            }
            else{
                un(fx,find(j+m));
                un(fy,find(i+m));
            }
        }
    }

    for(int i=1;i<=m;i++){
        if(vis[i]){
            continue;
        }
        if(find(i)==find(i+m)){
            return false;
        }
    }

    return true;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=m;i++){
            x[i]=read(),y[i]=read();
        }
        for(int i=1;i<=n;i++){
            int x=read();
            id[x]=i;
        }

        if(m>3*n+6){
            cout<<"NO"<<endl;
            continue;
        }

        for(int i=1;i<=m;i++){
            vis[i]=false;
            fa[i]=i;
            fa[i+m]=i+m;
        }

        for(int i=1;i<=m;i++){
            int a=id[x[i]];
            int b=id[y[i]];
            x[i]=min(a,b);
            y[i]=max(a,b);
        }

        for(int i=1;i<=m;i++){
            if(y[i]==x[i]+1||(x[i]==1&&y[i]==n)){
                vis[i]=true;
            }
        }

        if(compute()){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}