#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m,q;

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int to[MAXN][MAXB];

map<pair<int,int>,int>mp;

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

void prepare(){
    blen=sqrt(m);
    bnum=(m+blen-1)/blen;
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(m,i*blen);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=bnum;j++){
            to[i][j]=i;
        }
    }
}

int main()
{
    n=read(),m=read(),q=read();
    prepare();

    while(q--){
        int op=read();
        if(op==1){
            int u,v;
            u=read(),v=read();
            mp[{u,v}]=u+1;
            mp[{u+1,v}]=u;

            int x=u,y=u+1;
            int b=bi[v];
            for(int i=v-1;i>=bl[b];i--){
                if(mp.find({x,i})!=mp.end()){
                    x=mp[{x,i}];
                }
                
                if(mp.find({y,i})!=mp.end()){
                    y=mp[{y,i}];
                }
            }
            swap(to[x][b],to[y][b]);
        }
        else{
            int u=read();
            for(int i=1;i<=bnum;i++){
                u=to[u][i];
            }
            cout<<u<<endl;
        }
    }

    return 0;
}