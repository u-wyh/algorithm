#include<iostream>
#include<cstdio>
using namespace std;

long long tree[4000010],lazy[4000010],a[1000010],n,m;long long sum;
bool qwq[1000010];
void push_down(long long o,long long l,long long r){
    long long mid=l+r>>1;
    tree[o<<1]+=lazy[o]*(mid-l+1);tree[o<<1|1]+=lazy[o]*(r-mid);
    lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];
    lazy[o]=0;
}
void update(long long o,long long l,long long r,long long ql,long long qr,long long v){
    if(l>=ql&&r<=qr){tree[o]+=(r-l+1)*v;lazy[o]+=v;return;}
    long long mid=l+r>>1;
    push_down(o,l,r);
    if(mid>=ql) update(o<<1,l,mid,ql,qr,v);
    if(mid<qr) update(o<<1|1,mid+1,r,ql,qr,v);
    tree[o]=tree[o<<1]+tree[o<<1|1];
}
long long query(long long o,long long l,long long r,long long ql,long long qr){
    if(l>=ql&&r<=qr) return tree[o];
    long long mid=l+r>>1,ans=0;
    push_down(o,l,r);
    if(mid>=ql) ans+=query(o<<1,l,mid,ql,qr);
    if(mid<qr) ans+=query(o<<1|1,mid+1,r,ql,qr);
    return ans;
}
long long pos(long long x){
    long long l=1,r=500000;
    while(l<r){
        long long mid=l+r>>1;
        if(query(1,1,500000,mid,mid)>=x) r=mid;
        else l=mid+1;
    }
    return l;
}

inline long long read(){
    long long x=0,gf=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') gf=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
    return x*gf;
}

int main(){
    cin>>n>>m;
    for(long long i=1;i<=n;i++) a[i]=read(),update(1,1,500000,i,500000,1),sum+=a[i],qwq[i]=1;
    while(m--){
    	char c;cin>>c;
    	if(c=='Q') cout<<sum<<'\n';
    	else if(c=='C') {long long x=read(),y=read();a[x]-=y;sum-=y;}
    	else if(c=='I'){
    		long long x=read(),y=read();
    		if(qwq[x]){
    			sum-=a[x];sum+=y;a[x]=y;
    		}
    		else{sum+=y;a[x]=y;qwq[x]=1;update(1,1,500000,x,500000,1);}
    	}
    	else{
    		long long x=read();x=pos(x);sum-=a[x];a[x]=0;qwq[x]=0;update(1,1,500000,x,500000,-1);
    	}
    }
    return 0;
}
