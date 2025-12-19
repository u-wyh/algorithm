#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*20;

int n,m,k;

int fa[MAXN];
int sz[MAXN];
int traceback[MAXT][2];
int opsize;

int head[MAXN<<2];
int nxt[MAXT];
int tox[MAXT];
int toy[MAXT];
int cnt=1;

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

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void undo(){
    int fx=traceback[opsize][0];
    int fy=traceback[opsize][1];
    fa[fy]=fy;
    sz[fx]-=sz[fy];
    opsize--;
}

void addedge(int u,int x,int y){
    nxt[cnt]=head[u];
    tox[cnt]=x;
    toy[cnt]=y;
    head[u]=cnt++;
}

void add(int jobl,int jobr,int jobx,int joby,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        addedge(i,jobx,joby);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobx,joby,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobx,joby,mid+1,r,i<<1|1);
        }
    }
}

void un(int x,int y){
    if(sz[x]<sz[y]){
        swap(x,y);
    }
    fa[y]=x;
    sz[x]+=sz[y];
    ++opsize;
    traceback[opsize][0]=x;
    traceback[opsize][1]=y;
}

void dfs(int l,int r,int i){
    bool flag=false;
    int unioncnt=0;
    for(int ei=head[i];ei;ei=nxt[ei]){
        int x=tox[ei];
        int y=toy[ei];
        int fx=find(x);
        int fy=find(y);
        if(fx==fy){
            flag=true;
            break;
        }
        else{
            un(fx,fy);
            unioncnt++;
        }
    }

    if(flag){
        for(int p=l;p<=r;p++){
            cout<<"Yes\n";
        }
    }
    else{
        if(l==r){
            cout<<"No\n";
        }
        else{
            int mid=(l+r)>>1;
            dfs(l,mid,i<<1);
            dfs(mid+1,r,i<<1|1);
        }
    }

    while(unioncnt){
        undo();
        unioncnt--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=2*n;i++){
        fa[i]=i;
        sz[i]=1;
    }

    for(int i=1;i<=m;i++){
        int x=read();
        int y=read()+n;
        mp[{x,y}]=1;
    }

    k=read();
    for(int i=1;i<=k;i++){
        int x=read();
        int y=read()+n;
        if(mp.count({x,y})&&mp[{x,y}]){
            add(mp[{x,y}],i-1,x,y,1,k,1);
            mp[{x,y}]=0;
        }
        else{
            mp[{x,y}]=i;
        }
    }

    for(auto it=mp.begin();it!=mp.end();it++){
        if(it->second!=0){
            add(it->second,k,it->first.first,it->first.second,1,k,1);
        }
    }
    dfs(1,k,1);
    return 0;
}