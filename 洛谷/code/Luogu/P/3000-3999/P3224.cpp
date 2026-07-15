#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*20;
const int INF = 1e9;

int n,m;
int val[MAXN];
int pos[MAXN];

int fa[MAXN];
int siz[MAXN];

int root[MAXN];
int cnt=0;
int key[MAXT];
int ls[MAXT];
int rs[MAXT];
int sz[MAXT];
double priority[MAXT];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int newnode(int val){
    ++cnt;
    key[cnt]=val;
    sz[cnt]=1;
    priority[cnt]=(double)rand()/RAND_MAX;
    return cnt;
}

void prepare(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        siz[i]=1;
    }
    for(int i=1;i<=n;i++){
        root[i]=newnode(val[i]);
    }
}

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        // 来到了空节点  说明分裂结束
        rs[l] = ls[r] = 0;
    } else {
        if (key[i] <= num) {
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

// 合并的时候按照优先级组织  维持整体的平衡性
int merge(int l, int r) {
    if (l == 0 || r == 0) {
        // 遇到了空树  直接结束
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void mergetree(int x,int y){
    queue<int>q;
    q.push(y);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        split(0,0,root[x],val[u]);
        int lm=rs[0];
        int r=ls[0];
        root[x]=merge(merge(lm,newnode(val[u])),r);
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            q.push(v);
        }
    }
    addedge(x,y);
    fa[y]=x;
    siz[x]+=siz[y];
}

int getrank(int k,int u){
    while(u){
        if(sz[ls[u]]+1==k){
            return key[u];
        }
        else if(sz[ls[u]]+1<k){
            k-=(sz[ls[u]]+1);
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    return u;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
        val[i]=n+1-val[i];
        pos[val[i]]=i;
    }
    prepare();
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        int fx=find(x),fy=find(y);
        if(fx!=fy){
            if(siz[fx]<siz[fy]){
                swap(fx,fy);
            }
            mergetree(fx,fy);
        }
    }
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        char op;
        int u,v;
        scanf(" %c %d %d",&op,&u,&v);
        if(op=='B'){
            int fx=find(u),fy=find(v);
            if(fx!=fy){
                if(siz[fx]<siz[fy]){
                    swap(fx,fy);
                }
                mergetree(fx,fy);
            }
        }
        else{
            u=find(u);
            if(siz[u]<v){
                printf("-1\n");
            }
            else{
                printf("%d\n",pos[getrank(siz[u]-v+1,root[u])]);
            }
        }
    }
    return 0;
}