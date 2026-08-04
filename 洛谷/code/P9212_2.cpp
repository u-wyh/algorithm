#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXQ = 5e5+5;
const int MAXB = 705;

int n,q,limit,maxv;
int val[MAXN];

int headq[MAXB];
int nxtq[MAXQ<<2];
int qid[MAXQ<<2];
int qk[MAXQ<<2];
int qx[MAXQ<<2];
int ql[MAXQ<<2];
int qr[MAXQ<<2];
int cntq=1;

int qord[MAXQ<<2];

int reminder[MAXN];
int valcnt[MAXN];
int b;
int bl[MAXB];
int br[MAXB];
int valbelong[MAXN];
int valblock[MAXB];

int bigcnt;
int bigl[MAXQ<<1];
int bigr[MAXQ<<1];
int bigx[MAXQ<<1];
int bigk[MAXQ<<1];
int bigm[MAXQ<<1];
int bigid[MAXQ<<1];

int ans[MAXQ];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

void addquerynode(int p,int x,int vl,int vr,int k,int id){
    nxtq[cntq]=headq[p];
    qid[cntq]=id;
    qk[cntq]=k;
    qx[cntq]=x;
    ql[cntq]=vl;
    qr[cntq]=vr;
    headq[p]=cntq++;
}

void addquery(int p,int vl,int vr,int xl,int xr,int k,int id){
    addquerynode(p,xr,vl,vr,k,id);
    addquerynode(p,xl-1,vl,vr,-k,id);
}

bool cmp(int x,int y){
    return qx[x]<qx[y];
}

int query(int l,int r){
    int ans=0;
    int lb=l/b+1;
    int rb=r/b+1;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            ans+=valcnt[i];
        }
    }
    else{
        for(int i=l;i<=lb*b-1;i++){
            ans+=valcnt[i];
        }
        for(int i=lb+1;i<rb;i++){
            ans+=valblock[i];
        }
        for(int i=(rb-1)*b;i<=r;i++){
            ans+=valcnt[i];
        }
    }
    return ans;
}

void computesml(){
    for(int p=1;p<=limit;p++){
        if(headq[p]==0){
            continue;
        }
        b=(int)sqrt(p);
        for(int i=1;i<=n;i++){
            reminder[i]=(val[i]%p);
        }
        for(int i=0;i<p;i++){
            valbelong[i]=(i/b)+1;
        }

        for(int i=0;i<p;i++){
            valcnt[i]=0;
        }
        for(int i=1;i<=(p-1)/b+1;i++){
            valblock[i]=0;
        }

        int cnt=0;
        for(int i=headq[p];i;i=nxtq[i]){
            qord[++cnt]=i;
        }
        sort(qord+1,qord+cnt+1,cmp);

        int cur=0;
        for(int i=1;i<=cnt;i++){
            int u=qord[i];
            int id=qid[u];
            while(cur+1<=n&&cur+1<=qx[u]){
                cur++;
                int val=reminder[cur];
                valcnt[val]++;
                valblock[valbelong[val]]++;
            }

            ans[id]+=qk[u]*query(ql[u],qr[u]);
        }
    }
}

bool cmp2(int x,int y){
    return bigx[x]<bigx[y];
}

// 查询当前前缀中，值位于[l,r]的数量
int querybig(int l,int r){
    l=max(l,0);
    r=min(r,maxv);

    if(l>r)
        return 0;

    int lb=valbelong[l];
    int rb=valbelong[r];

    if(lb==rb){
        int res=valcnt[r];

        if(l>bl[lb])
            res-=valcnt[l-1];

        return res;
    }

    // 左侧残块
    int res=valblock[lb]-valblock[lb-1];

    if(l>bl[lb])
        res-=valcnt[l-1];

    // 中间完整块
    res+=valblock[rb-1]-valblock[lb];

    // 右侧残块
    res+=valcnt[r];

    return res;
}

void computebig(){
    // 值域按照limit分块
    b=limit;
    int bcnt=maxv/b+1;

    for(int v=0;v<=maxv;v++){
        valcnt[v]=0;
        valbelong[v]=v/b+1;
    }

    for(int i=0;i<=bcnt;i++)
        valblock[i]=0;

    for(int i=1;i<=bcnt;i++){
        bl[i]=(i-1)*b;
        br[i]=min(maxv,i*b-1);
    }

    for(int i=1;i<=bigcnt;i++)
        qord[i]=i;

    sort(qord+1,qord+bigcnt+1,cmp2);

    int cur=0;

    for(int i=1;i<=bigcnt;i++){
        int u=qord[i];

        while(cur<n&&cur<bigx[u]){
            cur++;

            int v=val[cur];
            int p=valbelong[v];

            // 维护所在块的块内前缀和
            for(int j=v;j<=br[p];j++)
                valcnt[j]++;

            // 维护整块数量的前缀和
            for(int j=p;j<=bcnt;j++)
                valblock[j]++;
        }

        int res=0;

        // a mod m位于[bigl,bigr]
        // 等价于a位于若干个周期值域区间
        for(int base=0;base+bigl[u]<=maxv;base+=bigm[u]){
            int l=base+bigl[u];
            int r=min(maxv,base+bigr[u]);

            res+=querybig(l,r);
        }

        ans[bigid[u]]+=bigk[u]*res;
    }
}

void addbig(int m,int x,int l,int r,int k,int id){
    bigcnt++;
    bigid[bigcnt]=id;
    bigm[bigcnt]=m;
    bigk[bigcnt]=k;
    bigx[bigcnt]=x;
    bigl[bigcnt]=l;
    bigr[bigcnt]=r;
}

int main()
{
    n=read(),q=read();
    limit=700;
    for(int i=1;i<=n;i++){
        val[i]=read();
        maxv=max(maxv,val[i]);
    }

    for(int i=1;i<=q;i++){
        int l,r,x,y,m;
        l=read(),r=read(),x=read(),y=read(),m=read();
        x%=m,y%=m;
        if(m<=limit){
            if(x>y){
                addquery(m,m-x,m-y-1,l,r,1,i);
            }
            else if(x<y){
                ans[i]=r-l+1;
                addquery(m,m-y,m-x-1,l,r,-1,i);
            }
        }
        else{
            if(x>y){
                addbig(m,r,m-x,m-y-1,1,i);
                addbig(m,l-1,m-x,m-y-1,-1,i);
            }
            else if(x<y){
                ans[i]=r-l+1;
                addbig(m,r,m-y,m-x-1,-1,i);
                addbig(m,l-1,m-y,m-x-1,1,i);
            }
        }
    }

    computesml();
    computebig();

    for(int i=1;i<=q;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}