#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
char s[MAXN];
struct node{
    int len;
    int sum;
    bool change;
    int update;
}tree[26][MAXN<<2];

void up(int i,int op){
    tree[op][i].sum=tree[op][i<<1].sum+tree[op][i<<1|1].sum;
}

void build(int l,int r,int i,int op){
    tree[op][i].change=false;
    tree[op][i].len=r-l+1;
    tree[op][i].update=0;
    if(l==r){
        tree[op][i].sum=((s[l]-'a')==op)?1:0;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1,op);
        build(mid+1,r,i<<1|1,op);
        up(i,op);
    }
}

void lazy(int i,int v,int op){
    tree[op][i].sum=v*tree[op][i].len;
    tree[op][i].change=true;
    tree[op][i].update=v;
}

void down(int i,int op){
    if(tree[op][i].change){
        lazy(i<<1,tree[op][i].update,op);
        lazy(i<<1|1,tree[op][i].update,op);
        tree[op][i].change=false;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i,int op){
    // cout<<jobl<<' '<<jobr<<' '<<jobv<<' '<<l<<' '<<r<<' '<<i<<' '<<op<<endl;
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv,op);
    }
    else{
        int mid=(l+r)/2;
        down(i,op);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1,op);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1,op);
        }
        up(i,op);
    }
}

int query(int jobl,int jobr,int l,int r,int i,int op){
    if(jobl<=l&&r<=jobr){
        return tree[op][i].sum;
    }
    else{
        int mid=(l+r)/2;
        down(i,op);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1,op);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1,op);
        }
        return ans;
    }
}

void compute(int l,int r){
    int cnt=0;
    int vis[26];
    for(int i=0;i<26;i++){
        vis[i]=0;
    }
    for(int i=0;i<26;i++){
        vis[i]=query(l,r,1,n,1,i);
        if(vis[i]%2==1){
            cnt++;
        }
    }
    // cout<<l<<' '<<r<<' '<<cnt<<endl;
    if(cnt>=2){
        return ;
    }
    int st=l,en=r;
    for(int i=0;i<26;i++){
        if(vis[i]==0){
            continue;
        }
        update(l,r,0,1,n,1,i);
        if(vis[i]%2==1){
            update((l+r)/2,(l+r)/2,1,1,n,1,i);
        }
        int len=vis[i]/2;
        update(st,st+len-1,1,1,n,1,i);
        update(en-len+1,en,1,1,n,1,i);
        st=st+len;
        en=en-len;
    }
}

void fun(int l,int r,int i,int op){
    if(l==r){
        s[l]=char(op+'a');
    }
    else{
        int mid=(l+r)/2;
        down(i,op);
        if(tree[op][i<<1].sum){
            fun(l,mid,i<<1,op);
        }
        if(tree[op][i<<1|1].sum){
            fun(mid+1,r,i<<1|1,op);
        }
    }
}

int main()
{
    #ifdef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    scanf("%d %d %s",&n,&m,s+1);
    for(int i=0;i<26;i++){
        build(1,n,1,i);
    }
    for(int i=1;i<=m;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        compute(l,r);
    }
    for(int i=0;i<26;i++){
        fun(1,n,1,i);
    }
    printf("%s",s+1);
    return 0;
}