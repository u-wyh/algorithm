#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m,d,s;

int val[MAXN];

int u[MAXN];
int v[MAXN];
int ok[MAXN];
map<pair<int,int>,int>mp;

int op[MAXN];
int x[MAXN];
int y[MAXN];

int lt[MAXN];
int rt[MAXN];

int fainit[MAXN];
int szinit[MAXN];

int fa[MAXN];
int sz[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int qx[MAXN];
int qy[MAXN];
int qz[MAXN];

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=val[i];
    }
    for(int i=1;i<=m;i++){
        if(ok[i]){
            un(u[i],v[i]);
        }
    }
    for(int i=1;i<=n;i++){
        fainit[i]=fa[i];
        szinit[i]=sz[i];
    }
    for(int i=1;i<=s;i++){
        lt[i]=-1;
        rt[i]=d;
    }
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void init(){
    for(int i=0;i<=d;i++){
        head[i]=0;
    }
    cntg=1;
    for(int i=1;i<=n;i++){
        fa[i]=fainit[i];
        sz[i]=szinit[i];
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>d>>s;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        if(u[i]>v[i]){
            swap(u[i],v[i]);
        }
        mp[{u[i],v[i]}]=i;
        ok[i]=true;
    }

    for(int i=1;i<=d;i++){
        cin>>op[i]>>x[i]>>y[i];
        if(op[i]==1){
            if(x[i]>y[i]){
                swap(x[i],y[i]);
            }
            ok[mp[{x[i],y[i]}]]=false;
        }
        else{
            val[x[i]]-=y[i];
        }
    }

    for(int i=1;i<=s;i++){
        cin>>qx[i]>>qy[i]>>qz[i];
    }

    prepare();

    bool flag=true;
    while(flag){
        init();
        flag=false;
        for(int i=1;i<=s;i++){
            if(lt[i]<rt[i]){
                flag=true;
                int mid=(lt[i]+rt[i]+1)/2;
                addedge(mid,i);
            }
        }
        // 这个是特判 实际上只有lt=d rt=d+1的时候才可能会有
        for(int ei=head[d];ei;ei=nxt[ei]){
            int id=to[ei];
            int x=qx[id];
            int y=qy[id];
            int z=qz[id];
            if(sz[find(x)]+sz[find(y)]>=z){
                lt[id]=d;
            }
            else{
                rt[id]=d-1;
            }
        }
        for(int i=d;i>=1;i--){
            if(op[i]==1){
                un(x[i],y[i]);
            }
            else{
                sz[find(x[i])]+=y[i];
            }

            for(int ei=head[i-1];ei;ei=nxt[ei]){
                int id=to[ei];
                int x=qx[id];
                int y=qy[id];
                int z=qz[id];
                if(sz[find(x)]+sz[find(y)]>=z){
                    lt[id]=i-1;
                }
                else{
                    rt[id]=i-2;
                }
            }
        }
    }
    for(int i=1;i<=s;i++){
        cout<<lt[i]<<endl;
    }
    return 0;
}