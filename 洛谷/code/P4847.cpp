#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int ls[MAXN];
int rs[MAXN];
int fa[MAXN];
int sz[MAXN];
double priority[MAXN];
int val[MAXN];
long long sum[MAXN];

void up(int x){
    if(x==0){
        return ;
    }
    sz[x]=sz[ls[x]]+sz[rs[x]]+1;
    sum[x]=sum[ls[x]]+sum[rs[x]]+val[x];
    if(ls[x]){
        fa[ls[x]]=x;
    }
    if(rs[x]){
        fa[rs[x]]=x;
    }
}

void split(int l,int r,int i,int num){
    if(i==0){
        rs[l]=ls[r]=0;
        return ;
    }
    if(sz[ls[i]]+1<=num){
        rs[l]=i;
        fa[i]=l;
        split(i,r,rs[i],num-sz[ls[i]]-1);
        up(i);
    }
    else{
        ls[r]=i;
        fa[i]=r;
        split(l,i,ls[i],num);
        up(i);
    }
}

int merge(int l,int r){
    if(l==0||r==0){
        int ans=l+r;
        if(ans){
            fa[ans]=0;
        }
        return ans;
    }
    if(priority[l]<priority[r]){
        rs[l]=merge(rs[l],r);
        up(l);
        fa[l]=0;
        return l;
    }
    else{
        ls[r]=merge(l,ls[r]);
        up(r);
        fa[r]=0;
        return r;
    }
}

int getroot(int x){
    while(fa[x]){
        x=fa[x];
    }
    return x;
}

int getrank(int x){
    int ans=sz[ls[x]]+1;
    while(fa[x]){
        int f=fa[x];
        if(rs[f]==x){
            ans+=sz[ls[f]]+1;
        }
        x=f;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        ls[i]=rs[i]=fa[i]=0;
        sz[i]=1;
        sum[i]=val[i];
        priority[i]=(double)rand()/RAND_MAX;
    }

    for(int i=1;i<=m;i++){
        char op;
        int x,y;
        cin>>op;
        if(op=='M'){
            cin>>x>>y;
            int fx=getroot(x);
            int fy=getroot(y);
            if(fx!=fy){
                merge(fy,fx);
            }
        }
        else if(op=='D'){
            cin>>x;
            int rt=getroot(x);
            int rk=getrank(x);
            split(0,0,rt,rk-1);
        }
        else{
            cin>>x>>y;
            int rx=getroot(x);
            int ry=getroot(y);
            if(rx!=ry){
                cout<<-1<<endl;
                continue;
            }
            int px=getrank(x);
            int py=getrank(y);
            if(px>py){
                swap(px,py);
            }
            split(0,0,rx,py);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,px-1);
            int l=rs[0];
            int mid=ls[0];
            cout<<sum[mid]<<endl;
            merge(merge(l,mid),r);
        }
    }
    return 0;
}