#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,m,ans=0;
int tree[MAXN<<2];
int tree1[MAXN<<2];
bool cut[MAXN<<2],add[MAXN<<2];
int len[MAXN<<2];

void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
    tree1[i]=tree1[i<<1]+tree1[i<<1|1];
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=1;
        tree1[i]=1;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    cut[i]=add[i]=false;
    len[i]=r-l+1;
}

void downlazy(int i){
    tree[i]=tree1[i]=0;
    cut[i]=true;
    add[i]=false;
}

void addlazy(int i){
    if(cut[i]){
        tree[i]=0;
        downlazy(i<<1);
        downlazy(i<<1|1);
    }
    tree1[i]=len[i];
    add[i]=true;
    cut[i]=false;
}

void down(int i){
    if(cut[i]){
        cut[i]=false;
        downlazy(i<<1);
        downlazy(i<<1|1);
    }
    if(add[i]){
        add[i]=false;
        addlazy(i<<1);
        addlazy(i<<1|1);
    }
}

void cutt(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        downlazy(i);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            cutt(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            cutt(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void addd(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            addd(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            addd(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree1[i];
    }
    else{
        int ans=0;
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        //up(i);
        return ans;
    }
}

int main()
{
    cin>>n>>m;
    n++;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,u,v;
        cin>>op>>u>>v;
        u++,v++;
        if(op==0){
            cutt(u,v,1,n,1);
        }
        else{
            int tmp=query(u,v,1,n,1);
            ans+=(v-u+1-tmp);
            addd(u,v,1,n,1);
        }
    }
    cout<<(tree1[1]-tree[1])<<endl<<(ans-tree1[1]+tree[1]);
    return 0;
}
