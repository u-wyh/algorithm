// https://www.luogu.com.cn/problem/P6707
// 这道题是将块状链表和懒更新结合在一起实现 很考察能力
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 2e5+5;
const int MAXB = 2005;

int n,q;

// 这是每个单点的信息
int cnt;
int bi[MAXN];
int val[MAXN];
int nxt[MAXN];
int pre[MAXN];

// 这是块的信息
int blen;
int blockcnt;
int bl[MAXB];
int br[MAXB];
int sum[MAXB];
bool change[MAXB];
int tag[MAXB];
int s[MAXB];
int d[MAXB];
int nxtb[MAXB];
int preb[MAXB];
int sz[MAXB];

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

void prepare(){
    for(int i=1;i<=n;i++){
        pre[i]=i-1;
        nxt[i]=i+1;
    }
    cnt=n;

    blen=min((int)(sqrt(n)+1),400ll);
    blockcnt=(n+blen-1)/blen;
    for(int i=1;i<=blockcnt;i++){
        nxtb[i]=i+1;
        preb[i]=i-1;
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
        sz[i]=br[i]-bl[i]+1;
    }
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
        sum[bi[i]]+=val[i];
    }
}

inline void updatelazy(int i,int x){
    for(int pos=bl[i];pos!=nxt[br[i]];pos=nxt[pos]){
        val[pos]=x;
    }
}

inline void addlazy(int i,int st,int dd){
    int len=0;
    for(int pos=bl[i];pos!=nxt[br[i]];pos=nxt[pos]){
        val[pos]+=st+len*dd;
        len++;
    }
}

inline void down(int i){
    if(change[i]){
        updatelazy(i,tag[i]);
        change[i]=false;
        tag[i]=0;
    }
    if(s[i]||d[i]){
        addlazy(i,s[i],d[i]);
        s[i]=0,d[i]=0;
    }
}

void update(int l,int r,int x){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        down(lb);
        for(int pos=l;pos!=nxt[r];pos=nxt[pos]){
            sum[lb]-=(val[pos]-x);
            val[pos]=x;
        }
    }
    else{
        down(lb);
        for(int pos=l;pos!=nxt[br[lb]];pos=nxt[pos]){
            sum[lb]-=(val[pos]-x);
            val[pos]=x;
        }
        for(int b=nxtb[lb];b!=rb;b=nxtb[b]){
            change[b]=true,tag[b]=x;
            s[b]=0,d[b]=0;
            sum[b]=sz[b]*x;
        }
        down(rb);
        for(int pos=bl[rb];pos!=nxt[r];pos=nxt[pos]){
            sum[rb]-=(val[pos]-x);
            val[pos]=x;
        }
    }
}

void add(int l,int r,int x){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        down(lb);
        int len=1;
        for(int pos=l;pos!=nxt[r];pos=nxt[pos]){
            sum[lb]+=x*len;
            val[pos]+=x*len;
            len++;
        }
    }
    else{
        down(lb);
        int len=1;
        for(int pos=l;pos!=nxt[br[lb]];pos=nxt[pos]){
            sum[lb]+=x*len;
            val[pos]+=x*len;
            len++;
        }
        for(int b=nxtb[lb];b!=rb;b=nxtb[b]){
            s[b]+=len*x;
            d[b]+=x;
            sum[b]+=sz[b]*(sz[b]-1+2*len)/2*x;
            len+=sz[b];
        }
        down(rb);
        for(int pos=bl[rb];pos!=nxt[r];pos=nxt[pos]){
            sum[rb]+=x*len;
            val[pos]+=x*len;
            len++;
        }
    }
}

void insert(int block,int pos,int x){
    down(block);
    sz[block]++;
    ++cnt;
    bi[cnt]=block;
    nxt[cnt]=pos;
    pre[cnt]=pre[pos];
    pre[pos]=cnt;
    nxt[pre[cnt]]=cnt;
    val[cnt]=x;
    sum[block]+=x;
    if(pos==bl[block]){
        bl[block]=cnt;
    }

    if(sz[block]==2*blen){
        int old=sum[block];
        ++blockcnt;
        sz[blockcnt]=blen;
        sz[block]=blen;

        br[blockcnt]=br[block];
        int now=0;
        int len=blen;
        int pos=bl[block];
        while(len--){
            now+=val[pos];
            pos=nxt[pos];
        }
        sum[blockcnt]=old-now;
        sum[block]=now;
        br[block]=pre[pos];
        bl[blockcnt]=pos;

        for(int pos=bl[blockcnt];pos!=nxt[br[blockcnt]];pos=nxt[pos]){
            bi[pos]=blockcnt;
        }

        nxtb[blockcnt]=nxtb[block];
        preb[blockcnt]=block;
        preb[nxtb[block]]=blockcnt;
        nxtb[block]=blockcnt;
    }
}

int query(int l,int r){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        down(lb);
        int ans=0;
        for(int pos=l;pos!=nxt[r];pos=nxt[pos]){
            ans+=val[pos];
        }
        return ans;
    }
    else{
        int ans=0;
        down(lb);
        for(int pos=l;pos!=nxt[br[lb]];pos=nxt[pos]){
            ans+=val[pos];
        }
        for(int b=nxtb[lb];b!=rb;b=nxtb[b]){
            ans+=sum[b];
        }
        down(rb);
        for(int pos=bl[rb];pos!=nxt[r];pos=nxt[pos]){
            ans+=val[pos];
        }
        return ans;
    }
}

inline int queryblock(int len){
    int pos=1;
    while(len>sz[pos]){
        len-=sz[pos];
        pos=nxtb[pos];
    }
    return pos;
}

inline int query(int len){
    int pos=1;
    while(len>sz[pos]){
        len-=sz[pos];
        pos=nxtb[pos];
    }
    pos=bl[pos];
    len--;
    while(len--){
        pos=nxt[pos];
    }
    return pos;
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    for(int i=1;i<=q;i++){
        int op,l,r,pos,x;
        op=read();
        if(op==3){
            pos=read(),x=read();
            int b=queryblock(pos);
            pos=query(pos);
            insert(b,pos,x);
        }
        else{
            l=read(),r=read();
            l=query(l),r=query(r);
            if(op==4){
                printf("%lld\n",query(l,r));
            }
            else {
                x=read();
                if(op==1){
                    update(l,r,x);
                }
                else{
                    add(l,r,x);
                }
            }
        }
    }
    return 0;
}