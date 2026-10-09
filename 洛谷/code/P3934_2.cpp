// https://www.luogu.com.cn/problem/P3934
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXM = 2e7+5;

int n,m;
int val[MAXN];
int mod[31];
int len;

int tree[MAXN<<2];
int tag[MAXN<<2];

int phi[MAXM];
int pri[MAXM];
bool vis[MAXM];

void prepare(){
    int n=20000000;
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            pri[++len]=i;
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                phi[i*pri[j]]=phi[i]*pri[j];
                break;
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }
}

void prepare(int m){
    mod[0]=m;
    len=0;
    while(mod[len]!=1){
        ++len;
        mod[len]=phi[mod[len-1]];
    }
    mod[len+1]=1;
}

bool flag1=false;
bool flag2=false;

int power(int a,int b,int mod){
    if(a>=mod){
        flag1=true;
        a%=mod;
    }
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a;
            if(ans>=mod){
                flag2=true;
            }
            else if(flag1){
                flag2=true;
            }
            ans%=mod;
        }
        b>>=1;
        a=(a*a);
        if(a>=mod){
            flag1=true;
        }
        a%=mod;
    }
    return ans;
}

void lazy(int i,int v){
    tree[i]+=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(pos<=mid){
            return query(pos,l,mid,i<<1);
        }
        else{
            return query(pos,mid+1,r,i<<1|1);
        }
    }
}

int calc(int id,int limit,int d){
    val[id]=query(id,1,n,1);
    if(id==limit){
        flag2=false;
        if(val[id]>=mod[d]){
            flag2=true;
        }
        return val[id]%mod[d];
    }
    if(d==len){
        flag2=true;
        return 0;
    }
    int x=calc(id+1,limit,d+1);
    if(flag2){
        x+=mod[d+1];
    }
    flag1=flag2=false;
    return power(val[id],x,mod[d]);
}

int query(int l,int r,int p){
    prepare(p);
    return calc(l,r,0);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
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
    }
}

signed main()
{
    prepare();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    build(1,n,1);
    while(m--){
        int op,x,l,r;
        cin>>op>>l>>r>>x;
        if(op==1){
            add(l,r,x,1,n,1);
        }
        else{
            cout<<query(l,r,x)<<endl;
        }
    }
    return 0;
}