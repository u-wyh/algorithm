#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

int arr[MAXN];
int sum[MAXN];

struct node1{
    int val,mul;//表示区间和  乘法次数
}seg[MAXN<<2];

struct node{
    int val,add,mul,pos;
}tree[MAXN<<2];

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

//区间和线段树
void segup(int i){
    seg[i].val=seg[i<<1].val+seg[i<<1|1].val;
}

void segbuild(int l,int r,int i){
    seg[i].mul=1;
    if(l==r){
        seg[i].val=arr[l];
    }
    else{
        int mid=(l+r)/2;
        segbuild(l,mid,i<<1);
        segbuild(mid+1,r,i<<1|1);
        segup(i);
    }
}

void seglazy(int i){
    seg[i].val*=-1;
    seg[i].mul*=-1;
}

void segdown(int i){
    if(seg[i].mul!=1){
        seglazy(i<<1);
        seglazy(i<<1|1);
        seg[i].mul=1;
    }
}

void segmul(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        seglazy(i);
    }
    else{
        int mid=(l+r)/2;
        segdown(i);
        if(jobl<=mid){
            segmul(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            segmul(jobl,jobr,mid+1,r,i<<1|1);
        }
        segup(i);
    }
}

int segquery(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return seg[i].val;
    }
    else{
        int ans=0;
        segdown(i);
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans+=segquery(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=segquery(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

//前缀和线段树
void up(int l,int r,int i){
    if(tree[r].val<=tree[l].val){
        tree[i].val=tree[r].val;
        tree[i].pos=tree[r].pos;
    }
    else{
        tree[i].val=tree[l].val;
        tree[i].pos=tree[l].pos;
    }
}

void build(int l,int r,int i){
    tree[i].mul=1,tree[i].add=0;
    if(l==r){
        tree[i].val=sum[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i,i<<1,i<<1|1);
    }
}

void mullazy(int i,int val){
    tree[i].val*=val;
    tree[i].add*=val;
    tree[i].mul*=val;
}

void addlazy(int i,int val){
    tree[i].add+=val;
    tree[i].val+=val;
}

void down(int i){
    if(tree[i].mul!=1){
        mullazy(i<<1,tree[i].mul);
        mullazy(i<<1|1,tree[i].mul);
        tree[i].mul=1;
    }
    if(tree[i].add){
        addlazy(i<<1,tree[i].add);
        addlazy(i<<1|1,tree[i].add);
        tree[i].add=0;
    }
}

void mul(int jobl,int jobr,int val,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        mullazy(i,val);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            mul(jobl,jobr,val,l,mid,i<<1);
        }
        if(jobr>mid){
            mul(jobl,jobr,val,mid+1,r,i<<1|1);
        }
        up(i,i<<1,i<<1|1);
    }
}

void add(int jobl,int jobr,int val,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,val);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,val,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,val,mid+1,r,i<<1|1);
        }
        up(i,i<<1,i<<1|1);
    }
}

node up(node a,node b){
    node ans;
    if(a.val<b.val){
        ans.val=a.val;
        ans.pos=a.pos;
    }
    else{
        ans.val=b.val;
        ans.pos=b.pos;
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        node ans;
        down(i);
        int mid=(l+r)/2;
        if(jobl<=mid&&jobr>mid){
            ans=up(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobr>mid){
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        arr[i]=(c=='(')?1:-1;
        sum[i]=sum[i-1]+arr[i];
    }
    segbuild(1,n,1);
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read();
        if(op==1){
            u=read(),v=read();
            int tmp=segquery(u,v,1,n,1);
            int temp=segquery(1,v,1,n,1);
            add(v+1,n,-2*tmp,1,n,1);
            mul(u,v,-1,1,n,1);
            add(u,v,2*temp,1,n,1);
            segmul(u,v,1,n,1);
        }
        else{
            u=read();
            int l=u+1,r=n;
            int tmp=segquery(1,u-1,1,n,1);
            while(l<=r){
                int mid=(l+r)/2;
                if(query(u,mid,1,n,1).val>=tmp){
                    v=mid;
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(query(u,v,1,n,1).val==tmp){
                cout<<query(u,v,1,n,1).pos<<endl;
            }
            else{
                cout<<0<<endl;
            }
        }
    }
    return 0;
}
