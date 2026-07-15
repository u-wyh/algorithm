#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
char s[MAXN];
struct node{
    int pre=0,suf=4;//表示前面、后面一个是什么
    int kind=0;//表示颜色种类是否纯色、以及如果只有一个种类是什么颜色的
    //如果为0  表示不是纯色
    int lazy=0;
}tree[MAXN<<1];

inline node up(node a,node b){
    node c;
    c.pre=a.pre,c.suf=b.suf;
    if(a.kind==b.kind){
        c.kind=a.kind;
    }
    else{
        c.kind=0;
    }
    return c;
}

void build(int l,int r,int i){
    tree[i].lazy=0;
    if(l==r){
        if(l==1){
            tree[i].pre=0;
            tree[i].suf=s[l+1]-'A'+1;
        }
        else if(l==n){
            tree[i].pre=s[l-1]-'A'+1;
            tree[i].suf=4;
        }
        else{
            tree[i].pre=s[l-1]-'A'+1;
            tree[i].suf=s[l+1]-'A'+1;
        }
        tree[i].kind=s[l]-'A'+1;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
    //cout<<i<<": "<<l<<' '<<r<<' '<<tree[i].pre<<' '<<tree[i].suf<<' '<<tree[i].kind<<endl;
}

void downlazy(int i,int op){
    tree[i].kind=op;
    tree[i].pre=tree[i].suf=op;
    tree[i].lazy=op;
}

void down(int i){
    if(tree[i].lazy){
        downlazy(i<<1,tree[i].lazy);
        downlazy(i<<1|1,tree[i].lazy);
        tree[i].lazy=0;
    }
}

void update(int jobl,int jobr,int op,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        downlazy(i,op);
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        if(jobl<=mid){
            update(jobl,jobr,op,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,op,mid+1,r,i<<1|1);
        }
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

void change(int pos,int pf,int op,int l,int r,int i){
    if(l==r){
        if(pf==1){
            tree[i].suf=op;
        }
        else{
            tree[i].pre=op;
        }
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        if(pos<=mid){
            change(pos,pf,op,l,mid,i<<1);
        }
        else{
            change(pos,pf,op,mid+1,r,i<<1|1);
        }
        tree[i]=up(tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        down(i);
        int mid=(l+r)>>1;
        node tmp;
        if(jobl<=mid&&jobr>mid){
            tmp=up(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            tmp=query(jobl,jobr,l,mid,i<<1);
        }
        else{
            tmp=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return tmp;
    }
}

int main()
{
    cin>>n;
    scanf("%s",s+1);
    build(1,n,1);
    cin>>m;
    for(int i=1;i<=m;i++){
        char op;
        int l,r;
        cin>>op>>l>>r;
        if(op=='A'){
            int v;
            char tmp;
            cin>>tmp;
            v=tmp-'A'+1;
            update(l,r,v,1,n,1);
            if(l>1){
                change(l-1,2,v,1,n,1);
                change(l,1,query(l-1,l-1,1,n,1).kind,1,n,1);
            }
            else{
                change(l,1,0,1,n,1);
            }
            if(r<n){
                change(r+1,1,v,1,n,1);
                change(r,2,query(r+1,r+1,1,n,1).kind,1,n,1);
            }
            else{
                change(r,2,4,1,n,1);
            }
        }
        else{
            node tmp=query(l,r,1,n,1);
            if(tmp.kind&&(tmp.pre!=tmp.suf)){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
        }
    }
    return 0;
}
