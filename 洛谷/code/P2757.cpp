#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int BASE = 499;

int n;
int nums[MAXN];

int p[MAXN];

int tree[MAXN<<2];
int front[MAXN<<2];
int back[MAXN<<2];

struct node{
    int len,f,b;
};

void build(int l,int r,int i){
    tree[i]=r-l+1;
    if(l==r){
        return;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void up(int i){
    front[i]=front[i<<1]*p[tree[i<<1|1]]+front[i<<1|1];
    back[i]=back[i<<1|1]*p[tree[i<<1]]+back[i<<1];
}

void update(int pos,int l,int r,int i){
    if(l==r){
        front[i]=back[i]=1;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,l,mid,i<<1);
        }
        else{
            update(pos,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

node merge(node a,node b){
    return {a.len+b.len,a.f*p[b.len]+b.f,b.b*p[a.len]+a.b};
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return {tree[i],front[i],back[i]};
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid&&jobr>mid){
            return merge(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else if(jobr>mid){
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

signed main()
{
    p[0]=1;
    for(int i=1;i<=500000;i++){
        p[i]=p[i-1]*BASE;
    }
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        memset(tree,0,sizeof(tree));
        memset(front,0,sizeof(front));
        memset(back,0,sizeof(back));
        build(1,n,1);
        bool flag=false;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        for(int i=1;i<=n;i++){
            int len=min(nums[i]-1,n-nums[i]);
            update(nums[i],1,n,1);
            if(len==0){
                continue;
            }
            node lt=query(nums[i]-len,nums[i]-1,1,n,1);
            node rt=query(nums[i]+1,nums[i]+len,1,n,1);
            if(lt.b!=rt.f){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<'Y'<<endl;
        }
        else{
            cout<<'N'<<endl;
        }
    }
    return 0;
}