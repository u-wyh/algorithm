#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,q;
long long dist[MAXN];
int fa[MAXN];
int sz[MAXN];

void prepare(){
    for(int i=0;i<=n;i++){
        sz[i]=1;
        fa[i]=i;
    }
}

int find(int x){
    if(x!=fa[x]){
        int tmp=fa[x];
        fa[x]=find(tmp);
        dist[x]+=dist[tmp];
    }
    return fa[x];
}

void un(int l,int r,long long v){
    int lf=find(l);
    int rf=find(r);
    if(lf==rf){
        return ;
    }
    if(sz[lf]<sz[rf]){
        fa[lf]=rf;
        sz[rf]+=sz[lf];
        dist[lf]=dist[r]+v-dist[l];
    }
    else{
        fa[rf]=lf;
        sz[lf]+=sz[rf];
        dist[rf]=dist[l]-v-dist[r];
    }
}

void query(int l,int r){
    if(find(l)!=find(r)){
        cout<<"UNKNOWN"<<endl;
        return ;
    }
    cout<<(dist[l]-dist[r])<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    prepare();
    for(int i=1;i<=m;i++){
        int l,r;
        long long v;
        cin>>l>>r>>v;
        r++;
        un(l,r,v);
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        r++;
        query(l,r);
    }
    return 0;
}