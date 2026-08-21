#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXB = 405;
const int MAXL = 1005;

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

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int n,m,cntn;
int initval[MAXN<<1];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfn[MAXN<<1];
int dfncnt;

int bcnt;
int nums[MAXB][MAXL];
int sz[MAXB];
int nxtb[MAXB];
int val[MAXB][MAXL];
int vsz[MAXB];

int enterb[MAXN<<1];
int enterp[MAXN<<1];
int leaveb[MAXN<<1];
int leavep[MAXN<<1];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    dfn[++dfncnt]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
    dfn[++dfncnt]=-u;
}

void setpos(int x,int b,int p){
    if(x>0){
        enterb[x]=b;
        enterp[x]=p;
    }
    else{
        x=-x;
        leaveb[x]=b;
        leavep[x]=p;
    }
}

void rebuild(int b){
    vsz[b]=0;
    for(int i=1;i<=sz[b];i++){
        int x=nums[b][i];
        setpos(x,b,i);
        if(x>0){
            vsz[b]++;
            val[b][vsz[b]]=initval[x];
        }
    }
    sort(val[b]+1,val[b]+vsz[b]+1);
}

int compute1(int b,int l,int r,int x){
    int ans=0;
    for(int i=l;i<=r;i++){
        int t=nums[b][i];
        if(t>0&&initval[t]>x){
            ans++;
        }
    }
    return ans;
}

int find1(int b,int v){
    int l=1,r=vsz[b],ans=vsz[b]+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(val[b][mid]>v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int compute2(int b,int x){
    return vsz[b]-find1(b,x)+1;
}

int query(int u,int x){
    int lb=enterb[u];
    int lp=enterp[u];
    int rb=leaveb[u];
    int rp=leavep[u];

    int ans=0;
    if(lb==rb){
        ans=compute1(lb,lp,rp,x);
    }
    else{
        ans+=compute1(lb,lp,sz[lb],x);
        
        for(int b=nxtb[lb];b!=rb;b=nxtb[b]){
            ans+=compute2(b,x);
        }
        
        ans+=compute1(rb,1,rp,x);
    }
    return ans;
}

void update(int u,int x){
    int b=enterb[u];
    int v=initval[u];
    int p=find1(b,v)-1;
    for(int i=p+1;i<=vsz[b];i++){
        val[b][i-1]=val[b][i];
    }
    vsz[b]--;

    initval[u]=x;
    p=find1(b,x)-1;
    for(int i=vsz[b];i>p;i--){
        val[b][i+1]=val[b][i];
    }
    val[b][p+1]=x;
    vsz[b]++;
}

void split(int b){
    int nb=++bcnt;
    int mid=sz[b]/2;

    sz[nb]=sz[b]-mid;

    for(int i=1;i<=sz[nb];i++){
        nums[nb][i]=nums[b][mid+i];
    }

    sz[b]=mid;

    nxtb[nb]=nxtb[b];
    nxtb[b]=nb;

    rebuild(b);
    rebuild(nb);
}

void insert(int u,int x){
    int id=++cntn;
    initval[id]=x;
    
    int b=leaveb[u];
    int p=leavep[u];

    for(int i=sz[b];i>=p;i--){
        nums[b][i+2]=nums[b][i];
    }

    nums[b][p]=id;
    nums[b][p+1]=-id;
    sz[b]+=2;

    if(sz[b]>MAXB*2){
        split(b);
        return ;
    }
    else{
        for(int i=p;i<=sz[b];i++){
            setpos(nums[b][i],b,i);
        }
        p=find1(b,x)-1;
        for(int i=vsz[b];i>p;i--){
            val[b][i+1]=val[b][i];
        }
        val[b][p+1]=x;
        vsz[b]++;
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        initval[i]=read();
    }
    cntn=n;

    dfs(1,0);

    int lastb=0;
    for(int l=1;l<=dfncnt;l+=MAXB){
        int r=min(l+MAXB-1,dfncnt);
        int b=++bcnt;
        sz[b]=r-l+1;
        for(int i=l;i<=r;i++){
            nums[b][i-l+1]=dfn[i];
        }
        if(lastb){
            nxtb[lastb]=b;
        }
        lastb=b;
        rebuild(b);
    }

    m=read();
    int last=0;
    while(m--){
        int op,x,y;
        op=read(),x=read()^last,y=read()^last;
        if(op==0){
            last=query(x,y);
            write(last);
            putchar('\n');
        }
        else if(op==1){
            update(x,y);
        }
        else{
            insert(x,y);
        }
    }
    return 0;
}