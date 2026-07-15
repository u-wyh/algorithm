// 这道题的设置非常巧妙，需要多建一层节点
// 因为如果有一次合并的时候  一个全是黑色的要合并
// 那么另外一个可能会产生懒更新的标签
// 另外的那一个即使可能右边没有  但是实际上合并之后他应该有
// 也就是如果不多扩展一层  就会导致信息丢失
// 这道题首先要保证最初每个树节点个数是logn级别的
// 在合并的过程中  也是老节点复用
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = 1e7+5;

int n,m;
int ans;
int val[MAXN];

int rt[MAXN<<1];
int sum[MAXT];
int now[MAXT];
int ls[MAXT];
int rs[MAXT];
bool tag[MAXT];
int cntv;

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

void lazy(int i){
    if(i==0){
        return ;
    }
    now[i]=sum[i]-now[i];
    tag[i]=!tag[i];
}

void up(int x){
    now[x]=now[ls[x]]+now[rs[x]];
}

void down(int i){
    if(tag[i]){
        lazy(ls[i]);
        lazy(rs[i]);
        tag[i]=false;
    }
}

int newnode(int l,int r){
    int rt=++cntv;
    sum[rt]=r*r-(l-1)*(l-1);
    return rt;
}

int update(int jobl,int jobr,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=newnode(l,r);
    }
    if(jobl<=l&&r<=jobr){
        lazy(rt);
    }
    else{
        // down(rt);
        int mid=(l+r)>>1;


        ls[rt]=newnode(l,mid);
        rs[rt]=newnode(mid+1,r);


        if(jobl<=mid){
            ls[rt]=update(jobl,jobr,l,mid,ls[rt]);
        }
        if(jobr>mid){
            rs[rt]=update(jobl,jobr,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }

    if(now[t1]==0){
        return t2;
    }
    if(now[t2]==0){
        return t1;
    }

    if(now[t1]==sum[t1]){
        ans+=now[t2];
        lazy(t2);
        return t2;
    }
    if(now[t2]==sum[t2]){
        ans+=now[t1];
        lazy(t1);
        return t1;
    }

    if(l==r){
        if(now[t1]&&now[t2]){
            ans+=sum[t1];
            // now[t1]=0;
        }
        now[t1]^=now[t2];
        // else {
        //     now[t1]=now[t1]+now[t2];
        // }
    }
    else{
        int mid=(l+r)>>1;
        down(t1);down(t2);
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    return t1;
}

signed main()
{
    n=read();
    
    for(int i=1;i<=n;i++){
        val[i]=read();
        val[i]/=2;
        m=max(m,val[i]);
    }
    for(int i=1;i<=n;i++){
        rt[i]=update(1,val[i],1,m,rt[i]);
    }
    for(int i=1;i<n;i++){
        ans=0;
        int x,y;
        x=read(),y=read();
        rt[i+n]=merge(1,m,rt[x],rt[y]);
        cout<<ans*4<<endl;
    }
    return 0;
}