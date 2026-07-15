#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7e4+5;
const int MAXM = 150005;
const long long INF = 1e18;

int n,m,w,h;

int posx[MAXN];
int posy[MAXN];

long long dis[MAXN];

struct node{
    long long t;
    int l,r,u,d;
};
node nums[MAXM];

struct compare{
    bool operator()(node a,node b){
        return a.t>b.t;
    }
};
priority_queue<node,vector<node>,compare>heap;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt=1;

set<pair<int,int>> tree[MAXN<<2];

int cand[MAXN];
int candcnt;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void insert(int pos,int joby,int jobv,int l,int r,int i){
    tree[i].insert({joby,jobv});
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            insert(pos,joby,jobv,l,mid,i<<1);
        }
        else{
            insert(pos,joby,jobv,mid+1,r,i<<1|1);
        }
    }
}

void remove(int pos,int joby,int jobv,int l,int r,int i){
    auto it=tree[i].find({joby,jobv});
    if(it==tree[i].end()){
        return ;
    }
    tree[i].erase(it);

    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            remove(pos,joby,jobv,l,mid,i<<1);            
        }
        else{
            remove(pos,joby,jobv,mid+1,r,i<<1|1);
        }
    }
}

void query(int jobl,int jobr,int jobd,int jobu,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        auto itl=tree[i].lower_bound({jobd,0});
        auto itr=tree[i].upper_bound({jobu,MAXN});

        for(auto it=itl;it!=itr;it++){
            cand[++candcnt]=it->second;
        }
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            query(jobl,jobr,jobd,jobu,l,mid,i<<1);
        }
        if(jobr>mid){
            query(jobl,jobr,jobd,jobu,mid+1,r,i<<1|1);
        }
    }
}

void dijkstra(){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
    }
    dis[1]=0;
    remove(posx[1],posy[1],1,1,w,1);
    for(int i=head[1];i;i=nxt[i]){
        int v=to[i];
        heap.push(nums[v]);
    }

    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        candcnt=0;
        query(tmp.l,tmp.r,tmp.d,tmp.u,1,w,1);

        for(int i=1;i<=candcnt;i++){
            if(dis[cand[i]]>tmp.t){
                dis[cand[i]]=tmp.t;
                remove(posx[cand[i]],posy[cand[i]],cand[i],1,w,1);
                for(int ei=head[cand[i]];ei;ei=nxt[ei]){
                    int v=to[ei];
                    node temp=nums[v];
                    temp.t=dis[cand[i]]+nums[v].t;
                    heap.push(temp);
                }
            }
        }
    }
}

int main()
{
    n=read(),m=read(),w=read(),h=read();
    for(int i=1;i<=n;i++){
        posx[i]=read(),posy[i]=read();
    }
    for(int i=1;i<=m;i++){
        int u=read();
        addedge(u,i);
        nums[i].t=read(),nums[i].l=read(),nums[i].r=read(),nums[i].d=read(),nums[i].u=read();
    }
    
    for(int i=1;i<=n;i++){
        insert(posx[i],posy[i],i,1,w,1);
    }

    dijkstra();

    for(int i=2;i<=n;i++){
        printf("%lld\n",dis[i]);
    }
    return 0;
}