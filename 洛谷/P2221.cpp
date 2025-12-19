#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e5+5;

int n,m;

int sum1[MAXN<<2];
int sum2[MAXN<<2];
int sum3[MAXN<<2];
int tree1[MAXN<<2];
int tree2[MAXN<<2];
int tree3[MAXN<<2];
int tag[MAXN<<2];

struct node{
    int v1,v2,v3;
};

void build(int l,int r,int i){
    if(l==r){
        sum1[i]=1;
        sum2[i]=l;
        sum3[i]=l*l;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        sum1[i]=sum1[i<<1]+sum1[i<<1|1];
        sum2[i]=sum2[i<<1]+sum2[i<<1|1];
        sum3[i]=sum3[i<<1]+sum3[i<<1|1];
    }
}

void up(int i){
    tree1[i]=tree1[i<<1|1]+tree1[i<<1];
    tree2[i]=tree2[i<<1|1]+tree2[i<<1];
    tree3[i]=tree3[i<<1|1]+tree3[i<<1];
}

void lazy(int i,int val){
    tree1[i]+=val*sum1[i];
    tree2[i]+=val*sum2[i];
    tree3[i]+=val*sum3[i];
    tag[i]+=val;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
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
        up(i);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return {tree1[i],tree2[i],tree3[i]};
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        node ans={0,0,0};
        if(jobl<=mid){
            node tmp=query(jobl,jobr,l,mid,i<<1);
            ans.v1+=tmp.v1;
            ans.v2+=tmp.v2;
            ans.v3+=tmp.v3;
        }
        if(jobr>mid){
            node tmp=query(jobl,jobr,mid+1,r,i<<1|1);
            ans.v1+=tmp.v1;
            ans.v2+=tmp.v2;
            ans.v3+=tmp.v3;
        }
        return ans;
    }
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    build(1,n-1,1);
    while(m--){
        char op;
        int l,r,v;
        cin>>op>>l>>r;
        if(op=='C'){
            cin>>v;
            add(l,r-1,v,1,n-1,1);
        }
        else{
            if(l==r){
                cout<<"0/1"<<endl;
                continue;
            }
            node ans=query(l,r-1,1,n-1,1);
            int res=-ans.v3+(l+r-1)*ans.v2+(r-l*r)*ans.v1;
            int tmp=(r-l+1)*(r-l)/2;
            int t=gcd(tmp,res);
            res/=t;
            tmp/=t;
            cout<<res<<'/'<<tmp<<endl;
        }
    }
    return 0;
}