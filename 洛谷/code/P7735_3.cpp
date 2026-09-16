#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
const int BUFSIZE=1<<20;

char ibuf[BUFSIZE],obuf[BUFSIZE];
int ipos,ilen,opos;

inline char gc(){
    if(ipos==ilen){
        ilen=fread(ibuf,1,BUFSIZE,stdin);
        ipos=0;
    }
    return ibuf[ipos++];
}

inline int read(){
    int x=0;
    char c=gc();

    while(c<'0'||c>'9'){
        c=gc();
    }

    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=gc();
    }

    return x;
}

inline void pc(char c){
    if(opos==BUFSIZE){
        fwrite(obuf,1,opos,stdout);
        opos=0;
    }

    obuf[opos++]=c;
}

inline void write(int x){
    char s[12];
    int len=0;

    if(!x){
        s[len++]='0';
    }

    while(x){
        s[len++]=x%10+'0';
        x/=10;
    }

    while(len){
        pc(s[--len]);
    }

    pc('\n');
}

int n,m;
int colcnt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg;

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

int col[MAXN];
int lcol[MAXN];
int rcol[MAXN];
int lazy[MAXN];
int cnt[MAXN];
int sz[MAXN];

bool rev[MAXN];
int sta[MAXN];

void clear(){
    cntg=1;
    colcnt=n;

    for(int i=1;i<=n;i++){
        head[i]=0;

        fa[i]=0;
        ls[i]=0;
        rs[i]=0;

        col[i]=i;
        lcol[i]=i;
        rcol[i]=i;

        lazy[i]=0;
        cnt[i]=1;
        sz[i]=1;
        rev[i]=false;
    }
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void buildtree(){
    int top=0;

    sta[++top]=1;
    fa[1]=0;

    while(top){
        int u=sta[top--];

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];

            if(v==fa[u]){
                continue;
            }

            fa[v]=u;
            sta[++top]=v;
        }
    }
}

inline void up(int x){
    int l=ls[x];
    int r=rs[x];

    sz[x]=sz[l]+sz[r]+1;
    cnt[x]=cnt[l]+cnt[r]+1;

    lcol[x]=l?lcol[l]:col[x];
    rcol[x]=r?rcol[r]:col[x];

    if(l&&rcol[l]==col[x]){
        cnt[x]--;
    }

    if(r&&lcol[r]==col[x]){
        cnt[x]--;
    }
}

inline bool isroot(int x){
    return ls[fa[x]]!=x&&rs[fa[x]]!=x;
}

inline int lr(int x){
    return rs[fa[x]]==x;
}

inline void updatecolor(int x,int v){
    if(!x){
        return;
    }

    col[x]=v;
    lcol[x]=v;
    rcol[x]=v;

    cnt[x]=1;
    lazy[x]=v;
}

inline void reversex(int x){
    if(!x){
        return;
    }

    swap(ls[x],rs[x]);
    swap(lcol[x],rcol[x]);

    rev[x]^=1;
}

inline void down(int x){
    if(lazy[x]){
        updatecolor(ls[x],lazy[x]);
        updatecolor(rs[x],lazy[x]);

        lazy[x]=0;
    }

    if(rev[x]){
        reversex(ls[x]);
        reversex(rs[x]);

        rev[x]=false;
    }
}

inline void rotate(int x){
    int f=fa[x];
    int g=fa[f];
    int k=lr(x);
    int w=k?ls[x]:rs[x];

    if(!isroot(f)){
        if(rs[g]==f){
            rs[g]=x;
        }
        else{
            ls[g]=x;
        }
    }

    fa[x]=g;

    if(k){
        ls[x]=f;
        rs[f]=w;
    }
    else{
        rs[x]=f;
        ls[f]=w;
    }

    if(w){
        fa[w]=f;
    }

    fa[f]=x;

    up(f);
    up(x);
}

inline void splay(int x){
    int top=0;

    sta[++top]=x;

    for(int y=x;!isroot(y);y=fa[y]){
        sta[++top]=fa[y];
    }

    while(top){
        down(sta[top--]);
    }

    while(!isroot(x)){
        int f=fa[x];

        if(!isroot(f)){
            if(lr(x)==lr(f)){
                rotate(f);
            }
            else{
                rotate(x);
            }
        }

        rotate(x);
    }
}

inline void access(int x){
    for(int y=0;x;y=x,x=fa[x]){
        splay(x);
        rs[x]=y;
        up(x);
    }
}

inline void makeroot(int x){
    access(x);
    splay(x);
    reversex(x);
}

inline void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}

inline void pathupdate(int x,int y){
    split(x,y);
    updatecolor(y,++colcnt);
}

inline int pathquery(int x,int y){
    split(x,y);
    return sz[y]-cnt[y];
}

int main(){
    int T=read();

    while(T--){
        n=read();
        m=read();

        clear();

        for(int i=1;i<n;i++){
            int u=read();
            int v=read();

            addedge(u,v);
            addedge(v,u);
        }

        buildtree();

        for(int i=1;i<=m;i++){
            int op=read();
            int x=read();
            int y=read();

            if(op==1){
                pathupdate(x,y);
            }
            else{
                write(pathquery(x,y));
            }
        }
    }

    if(opos){
        fwrite(obuf,1,opos,stdout);
    }

    return 0;
}