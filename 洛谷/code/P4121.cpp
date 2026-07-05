#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int n,m;
int val[MAXN][MAXN];

struct node{
    int cnt[2];
    int fa[MAXN*2];
};
node tree[MAXN<<2];

int tmp[MAXN<<2];
int pos[MAXN<<2];

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

inline int find(int x,int *fa){
    return x==fa[x]?x:fa[x]=find(fa[x],fa);
}

inline bool un(int x,int y,int *fa){
    int fx=find(x,fa);
    int fy=find(y,fa);
    if(fx!=fy){
        fa[fx]=fy;
        return true;
    }
    return false;
}

void up(int x,int id){
    node &cur=tree[id];
    node &lt=tree[id<<1];
    node &rt=tree[id<<1|1];

    cur.cnt[0]=lt.cnt[0]+rt.cnt[0];
    cur.cnt[1]=lt.cnt[1]+rt.cnt[1];

    for(int i=1;i<=4*n;i++){
        tmp[i]=i;
    }
    for(int i=1;i<=2*n;i++){
        tmp[i]=find(i,lt.fa);
    }
    for(int i=1;i<=2*n;i++){
        tmp[i+2*n]=find(i,rt.fa)+2*n;
    }

    for(int i=1;i<=n;i++){
        if(val[x][i]==val[x+1][i]){
            int u=n+i;
            int v=2*n+i;

            if(un(u,v,tmp)){
                cur.cnt[val[x][i]]--;
            }
        }
    }

    for(int i=1;i<=2*n;i++){
        cur.fa[i]=i;
    }
    for(int i=1;i<=4*n;i++){
        pos[i]=-1;
    }
    for(int i=1;i<=n;i++){
        int root=find(i,tmp);
        if(pos[root]==-1){
            pos[root]=i;
        }
        else{
            un(pos[root],i,cur.fa);
        }
    }
    for(int i=1;i<=n;i++){
        int root=find(i+3*n,tmp);
        if(pos[root]==-1){
            pos[root]=n+i;
        }
        else{
            un(pos[root],i+n,cur.fa);
        }
    }
}

void buildleaf(int x,int id){
    tree[id].cnt[0]=0;
    tree[id].cnt[1]=0;

    for(int i=1;i<=2*n;i++){
        tree[id].fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        if(i==1||val[x][i]!=val[x][i-1]){
            tree[id].cnt[val[x][i]]++;
        }
    }
    for(int i=1;i<=n;i++){
        un(i,i+n,tree[id].fa);
    }
    for(int i=1;i<n;i++){
        if(val[x][i]==val[x][i+1]){
            un(i,i+1,tree[id].fa);
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        buildleaf(l,i);
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(mid,i);
    }
}

void update(int pos,int l,int r,int i){
    if(l==r){
        buildleaf(pos,i);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,l,mid,i<<1);
        }
        else{
            update(pos,mid+1,r,i<<1|1);
        }
        up(mid,i);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            val[i][j]=read();
        }
    }
    build(1,n,1);

    m=read();
    for(int i=1;i<=m;i++){
        int x,y;
        x=read(),y=read();
        val[x][y]^=1;
        update(x,1,n,1);

        write(tree[1].cnt[1]);
        putchar(' ');
        write(tree[1].cnt[0]);
        putchar('\n');
    }
    return 0;
}