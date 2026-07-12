#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*20;

int n;
int arr[MAXN];
int pos[MAXN];

int suf[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int cntt;

int fa[MAXT];
int sz[MAXT];
int dis[MAXT];
bool used[MAXT];

bool ans=true;

int insert(int val,int l,int r,int i){
    int rt=++cntt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];

    if(l<r){
        int mid=(l+r)>>1;
        if(val<=mid){
            ls[rt]=insert(val,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(val,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int find(int x){
    if(fa[x]!=x){
        int f=fa[x];
        fa[x]=find(f);
        dis[x]^=dis[f];
    }
    return fa[x];
}

bool merge(int x,int y,int v){
    int fx=find(x);
    int fy=find(y);

    int dx=dis[x];
    int dy=dis[y];

    if(fx==fy){
        return (dx^dy)==v;
    }

    if(sz[fx]>sz[fy]){
        swap(fx,fy);
        swap(dx,dy);
    }

    fa[fx]=fy;
    dis[fx]=dx^dy^v;
    sz[fy]+=sz[fx];
    return true;
}

void activate(int p,int l,int r){
    if(p==0||used[p]||!ans){
        return ;
    }
    used[p]=true;

    if(l==r){
        ans&=merge(p,l,0);
    }
    else{
        int mid=(l+r)>>1;
        if(ls[p]){
            ans&=merge(p,ls[p],0);
            activate(ls[p],l,mid);
        }
        if(rs[p]){
            ans&=merge(p,rs[p],0);
            activate(rs[p],mid+1,r);
        }
    }
}

void addrange(int jobl,int jobr,int jobi,int l,int r,int i){
    if(i==0||!ans){
        return;
    }

    if(jobl<=l&&r<=jobr){
        ans&=merge(jobi,i,1);
        activate(i,l,r);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid)
            addrange(jobl,jobr,jobi,l,mid,ls[i]);
        if(jobr>mid)
            addrange(jobl,jobr,jobi,mid+1,r,rs[i]);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[arr[i]]=i;
    }
    for(int i=2;i<=n;i++){
        suf[i]=max(suf[i-1],pos[i-1]);
    }
    cntt=n;

    for(int i=n;i>=1;i--){
        root[i]=insert(pos[i],1,n,root[i+1]);
    }

    for(int i=1;i<=cntt;i++){
        fa[i]=i;
        sz[i]=1;
        dis[i]=0;
    }

    for(int i=1;i<=n&&ans;i++){
        int k=suf[arr[i]];

        if(k>i+1){
            addrange(i+1,k-1,i,1,n,root[arr[i]+1]);
        }
    }

    if(!ans){
        cout<<"NIE"<<endl;
    }
    else{
        cout<<"TAK"<<endl;
        for(int i=1;i<=n;i++){
            find(i);
            cout<<dis[i]+1<<' ';
        }
    }
    return 0;
}