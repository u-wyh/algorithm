#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
struct node{
    int ok=0,lr=0,rl=0;//lr rl都只能是0或者1  表示有或者没有
    bool all=false;//false表示全都是X
}tree[MAXN<<2];

node add(node a,node b){
    node c;
    if(!a.all&&!b.all){
        return c;
    }
    c.all=true;
    c.ok=a.ok+b.ok+a.rl*b.lr;
    if(!a.all){
        //表示a全都是x
        c.lr=b.lr,c.rl=b.rl;
        return c;
    }
    if(!b.all){
        c.lr=a.lr,c.rl=a.rl;
        return c;
    }
    c.lr=a.lr;
    c.rl=b.rl;
    return c;
}

void build(int l,int r,int i){
    if(l==r){
        if(l==1){
            tree[i].all=true;
            tree[i].rl=1;
        }
        else if(l==n){
            tree[i].all=true;
            tree[i].lr=1;
        }
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=add(tree[i<<1],tree[i<<1|1]);
    }
    //cout<<i<<": "<<l<<' '<<r<<' '<<tree[i].all<<' '<<tree[i].ok<<' '<<tree[i].lr<<' '<<tree[i].rl<<endl;
}

void update(int pos,int op,int l,int r,int i){
    if(l==r){
        if(op==0){
            tree[i].all=false;
            tree[i].ok=tree[i].lr=tree[i].rl=0;
        }
        else if(op==1){
            tree[i].all=true;
            tree[i].ok=tree[i].lr=0;
            tree[i].rl=1;
        }
        else{
            tree[i].all=true;
            tree[i].ok=tree[i].rl=0;
            tree[i].lr=1;
        }
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,op,l,mid,i<<1);
        }
        else{
            update(pos,op,mid+1,r,i<<1|1);
        }
        tree[i]=add(tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        node c;
        if(jobl<=mid&&jobr>mid){
            c=add(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobr>mid){
            c=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        else{
            c=query(jobl,jobr,l,mid,i<<1);
        }
        return c;
    }
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int pos,v;
            char tmp;
            cin>>pos>>tmp;
            if(tmp=='(')
                v=1;
            else if(tmp==')')
                v=2;
            else
                v=0;
            update(pos,v,1,n,1);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<query(l,r,1,n,1).ok<<endl;
        }
    }
    return 0;
}
