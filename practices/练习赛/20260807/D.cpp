#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,x;
int p[MAXN];
int q[MAXN];

int a[MAXN];
int b[MAXN];
int amin;
int bmin;

int ans[MAXN];
int anscnt;

int tree[2][MAXN<<2];

int query(int jobl,int jobr,int l,int r,int i,int op){
    if(jobl<=l&&r<=jobr){
        return tree[op][i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1,op));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1,op));
        }
        return ans;
    }
}

void up(int x,int op){
    tree[op][x]=max(tree[op][x<<1],tree[op][x<<1|1]);
}

void update(int pos,int l,int r,int i,int op){
    if(l==r){
        tree[op][i]=0;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,l,mid,i<<1,op);
        }
        else{
            update(pos,mid+1,r,i<<1|1,op);
        }
        up(i,op);
    }
}

void build(int l,int r,int i,int op){
    if(l==r){
        if(op==0){
            tree[op][i]=b[p[l]];
        }
        else{
            tree[op][i]=a[q[l]];
        }
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1,op);
        build(mid+1,r,i<<1|1,op);
        up(i,op);
    }
}

bool check(int v){
    // cout<<111<<endl;
    anscnt=0;
    build(1,n,1,0);
    build(1,n,1,1);

    amin=a[v];
    bmin=b[v];
    update(a[v],1,n,1,0);
    update(b[v],1,n,1,1);

    int v1=0,v2=0;
    while(true){
        v1=query(bmin+1,n,1,n,1,1);
        if(v1){
            if(v1>amin){
                break;
            }
            int id=p[v1];
            ans[++anscnt]=id;
            amin=v1;
            update(a[id],1,n,1,0);
            update(b[id],1,n,1,1);
            continue;
        }

        v2=query(amin+1,n,1,n,1,0);
        if(v2){
            if(v2>bmin){
                break;
            }
            int id=q[v2];
            ans[++anscnt]=id;
            bmin=v2;
            update(a[id],1,n,1,0);
            update(b[id],1,n,1,1);
            continue;
        }

        break;
    }
    return anscnt==(n-1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        a[p[i]]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>q[i];
        b[q[i]]=i;
    }

    if(check(x)){
        cout<<"YES"<<endl;
        for(int i=anscnt;i>=1;i--){
            cout<<ans[i]<<' ';
        }
        return 0;
    }
    cout<<"NO"<<endl;
    return 0;
}