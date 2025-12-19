#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

struct node{
    int lt,rt;
    long long lval,rval;
    int len;
    int ans;
    long long tag;
};
node tree[MAXN<<2];

void merge(node &u,node ls,node rs){
    bool flag=(ls.rval==rs.lval);
    u.len=ls.len+rs.len;
    u.lval=ls.lval;
    u.rval=rs.rval;
    u.ans=ls.ans+rs.ans;

    if(ls.ans==0&&rs.ans==0){
        if(flag){
            u.lt=ls.lt-1;
            u.rt=rs.rt-1;
            u.ans=1;
        }
        else{
            u.lt=u.rt=u.len;
        }
    }
    else if(ls.ans==0){
        u.rt=rs.rt;
        if(flag){
            u.lt=ls.lt-1;
            if(rs.lt){
                u.ans+=(rs.lt-1)/2+1;
            }
        }
        else{
            u.lt=ls.len+rs.lt;
        }
    }
    else if(rs.ans==0){
        u.lt=ls.lt;
        if(flag){
            u.rt=rs.rt-1;
            if(ls.rt){
                u.ans+=(ls.rt-1)/2+1;
            }
        }
        else{
            u.rt=rs.len+ls.rt;
        }
    }
    else{
        u.rt=rs.rt;
        u.lt=ls.lt;
        if(ls.rt==0&&rs.lt==0){
            if(flag){
                u.ans--;
            }
        }
        else if(ls.rt==0){
            if(flag){
                u.ans+=(rs.lt-1)/2;
            }
            else{
                u.ans+=rs.lt/2;
            }
        }
        else if(rs.lt==0){
            if(flag){
                u.ans+=(ls.rt-1)/2;
            }
            else{
                u.ans+=ls.rt/2;
            }
        }
        else{
            if(flag){
                u.ans+=(ls.rt-1)/2+(rs.lt-1)/2+1;
            }
            else{
                u.ans+=(ls.rt+rs.lt)/2;
            }
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].lval=tree[i].rval=val[l];
        tree[i].lt=tree[i].rt=tree[i].len=1;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        merge(tree[i],tree[i<<1],tree[i<<1|1]);
    }
}

void lazy(int i,long long val){
    tree[i].lval+=val;
    tree[i].rval+=val;
    tree[i].tag+=val;
}

void down(int i){
    if(tree[i].tag){
        lazy(i<<1,tree[i].tag);
        lazy(i<<1|1,tree[i].tag);
        tree[i].tag=0;
    }
}

void add(int jobl,int jobr,long long jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        merge(tree[i],tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;;
        down(i);
        if(jobl<=mid&&jobr>mid){
            node ans;
            merge(ans,query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
            return ans;
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    for(int i=1;i<n;i++){
        val[i]=val[i+1]-val[i];
    }
    n--;
    build(1,n,1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        char op;
        int s,t,a,b;
        scanf(" %c %d %d",&op,&s,&t);
        if(op=='A'){
            scanf("%d %d",&a,&b);
            if(s>1){
                add(s-1,s-1,a,1,n,1);
            }
            if(t<=n){
                add(t,t,-(1ll*a+1ll*(t-s)*b),1,n,1);
            }
            if(s<t){
                add(s,t-1,b,1,n,1);
            }
        }
        else{
            if(s==t){
                printf("1\n");
                continue;
            }
            node res=query(s,t-1,1,n,1);
            if(res.ans==0){
                printf("%d\n",(t-s+1+1)/2);
            }
            else{
                printf("%d\n",res.ans+(res.lt+1)/2+(res.rt+1)/2);
            }
        }
    }
    return 0;
}