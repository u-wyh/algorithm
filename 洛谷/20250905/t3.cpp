#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
int x[MAXN],y[MAXN];
int fa[MAXN];
map<pair<int,int>,int>mp;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

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

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=k+2;i++){
        fa[i]=i;
    }
    for(int i=1;i<=k;i++){
        int r,c;
        r=read(),c=read();
        mp[{r,c}]=i;
        for(int j=0;j<4;j++){
            int x=r+walk[j][0];
            int y=c+walk[j][1];
            if(mp[{x,y}]){
                un(i,mp[{x,y}]);
            }
        }
        if(r==1){
            un(i,k+1);
        }
        if(r==n-2){
            un(i,k+2);
        }
        if(find(k+1)==find(k+2)){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<"nej"<<endl;
    return 0;
}