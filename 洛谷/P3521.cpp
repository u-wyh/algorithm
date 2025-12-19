#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = 5e6+5;

int n;

int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
int cntv;

long long ans,no,yes;

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

void up(int x){
    sz[x]=sz[ls[x]]+sz[rs[x]];
}

int build(int jobv,int l,int r){
    int rt=++cntv;
    if(l==r){
        sz[rt]++;
    }
    else{
        int mid=(l+r)>>1;
        if(jobv<=mid){
            ls[rt]=build(jobv,l,mid);
        }
        else{
            rs[rt]=build(jobv,mid+1,r);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        sz[t1]+=sz[t2];
    }
    else{
        no+=1ll*sz[rs[t1]]*sz[ls[t2]];
        yes+=1ll*sz[rs[t2]]*sz[ls[t1]];
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    return t1;
}

int dfs(){
    int val=read();
    int rt;
    if(val==0){
        int left=dfs();
        int right=dfs();
        no=yes=0;
        rt=merge(1,n,left,right);
        ans+=min(no,yes);
    }
    else{
        rt=build(val,1,n);
    }
    return rt;
}

int main()
{
    n=read();
    dfs();
    cout<<ans<<endl;
    return 0;
}