#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

struct node{
    int o=0,i=0,oi=0,io=0,ioi=0;
}tree[MAXN<<2];
char s[MAXN];
int n,m;

void up(int i){
    tree[i].i=tree[i<<1].i+tree[i<<1|1].i;
    tree[i].o=tree[i<<1].o+tree[i<<1|1].o;
    tree[i].io=tree[i<<1].io+tree[i<<1|1].io+tree[i<<1].i*tree[i<<1|1].o;
    tree[i].oi=tree[i<<1].oi+tree[i<<1|1].oi+tree[i<<1].o*tree[i<<1|1].i;
    tree[i].ioi=tree[i<<1].ioi+tree[i<<1|1].ioi+tree[i<<1].io*tree[i<<1|1].i+tree[i<<1].i*tree[i<<1|1].oi;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].i=tree[i].o=0;
        if(s[l]=='I'){
            tree[i].i=1;
        }
        else{
            tree[i].o=1;
        }
        tree[i].io=tree[i].oi=tree[i].ioi=0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    //cout<<i<<": "<<l<<' '<<r<<' '<<tree[i].i<<' '<<tree[i].o<<' '<<tree[i].io<<' '<<tree[i].oi<<' '<<tree[i].ioi<<endl;
}

node add(node a,node b){
    node c;
    c.i=a.i+b.i;
    c.o=a.o+b.o;
    c.io=a.io+b.io+a.i*b.o;
    c.oi=a.oi+b.oi+a.o*b.i;
    c.ioi=a.ioi+b.ioi+a.io*b.i+a.i*b.oi;
    return c;
}

void update(int pos,int op,int l,int r,int i){
    if(l==r){
        if(op){
            tree[i].i=1;
            tree[i].o=0;
        }else{
            tree[i].i=0;
            tree[i].o=1;
        }
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,op,l,mid,i<<1);
        }else{
            update(pos,op,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        node ans;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans=add(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=add(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    cin>>n>>m;
    scanf("%s",s+1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==2){
            int l,r;
            cin>>l>>r;
            cout<<query(l,r,1,n,1).ioi<<endl;
        }
        else{
            int pos,v;
            char tmp;
            cin>>pos>>tmp;
            v=(tmp=='I')?1:0;
            update(pos,v,1,n,1);
        }
    }
    return 0;
}
