#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,q;

int head;
int cnt;
int val[MAXN];
int sum[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
int premax[MAXN],premin[MAXN];
int sufmax[MAXN],sufmin[MAXN];
int tag[MAXN];//覆盖标记
bool inv[MAXN];//字符翻转标记
bool rev[MAXN];//区间翻转标记

void up(int u){
    sum[u]=sum[ls[u]]+sum[rs[u]]+val[u];
    sz[u]=sz[ls[u]]+sz[rs[u]]+1;
    premax[u]=max(premax[ls[u]],sum[ls[u]]+val[u]+premax[rs[u]]);
    premin[u]=min(premin[ls[u]],sum[ls[u]]+val[u]+premin[rs[u]]);
    sufmax[u]=max(sufmax[rs[u]],sum[rs[u]]+val[u]+sufmax[ls[u]]);
    sufmin[u]=min(sufmin[rs[u]],sum[rs[u]]+val[u]+sufmin[ls[u]]);
}

void lazyinvert(int u){
    val[u]=-val[u];
    sum[u]=-sum[u];
    int x,y;
    x=premax[u],y=premin[u];
    premax[u]=-y,premin[u]=-x;
    x=sufmax[u],y=sufmin[u];
    sufmax[u]=-y,sufmin[u]=-x;
    inv[u]^=1;
    tag[u]=-tag[u];
}

void lazyreplace(int u,int v){
    val[u]=tag[u]=v;
    sum[u]=sz[u]*v;
    if(v==1){
        sufmin[u]=premin[u]=0;
        sufmax[u]=premax[u]=sum[u];
    }
    else{
        sufmin[u]=premin[u]=sum[u];
        sufmax[u]=premax[u]=0;
    }
    rev[u]=false;
    inv[u]=false;
}

void lazyreverse(int u){
    swap(ls[u],rs[u]);
    swap(premax[u],sufmax[u]);
    swap(premin[u],sufmin[u]);
    rev[u]^=1;
}

void down(int u){
    if(rev[u]){
        if(ls[u]){
            lazyreverse(ls[u]);
        }
        if(rs[u]){
            lazyreverse(rs[u]);
        }
        rev[u]=false;
    }
    if(inv[u]){
        if(ls[u]){
            lazyinvert(ls[u]);
        }
        if(rs[u]){
            lazyinvert(rs[u]);
        }
        inv[u]=false;
    }
    if(tag[u]){
        if(ls[u]){
            lazyreplace(ls[u],tag[u]);
        }
        if(rs[u]){
            lazyreplace(rs[u],tag[u]);
        }
        tag[u]=0;
    }
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void replace(int l,int r,int k){
    split(0,0,head,r);
    int lm=rs[0];
    int rt=ls[0];
    split(0,0,lm,l-1);
    lazyreplace(ls[0],k);
    head=merge(merge(rs[0],ls[0]),rt);
}

void reverse(int l,int r){
    split(0,0,head,r);
    int lm=rs[0];
    int rt=ls[0];
    split(0,0,lm,l-1);
    lazyreverse(ls[0]);
    head=merge(merge(rs[0],ls[0]),rt);
}

void invert(int l,int r){
    split(0,0,head,r);
    int lm=rs[0];
    int rt=ls[0];
    split(0,0,lm,l-1);
    lazyinvert(ls[0]);
    head=merge(merge(rs[0],ls[0]),rt);
}

int query(int l,int r){
    split(0,0,head,r);
    int lm=rs[0];
    int rt=ls[0];
    split(0,0,lm,l-1);
    int ans=(premax[ls[0]]+1)/2+(abs(sufmin[ls[0]])+1)/2;
    head=merge(merge(rs[0],ls[0]),rt);
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        int v=(c=='(')?-1:1;

        ++cnt;
        val[cnt]=v;
        sum[cnt]=v;
        sz[cnt]=1;
        priority[cnt]=(double)rand()/RAND_MAX;
        if(v==1){
            premax[cnt]=sufmax[cnt]=1;
        }
        else{
            premin[cnt]=sufmin[cnt]=-1;
        }
        head=merge(head,cnt);
    }

    while(q--){
        string s;
        int l,r;
        cin>>s>>l>>r;
        if(s[0]=='R'){
            char c;
            cin>>c;
            replace(l,r,(c==')')?1:-1);
        }
        else if(s[0]=='S'){
            reverse(l,r);
        }
        else if(s[0]=='I'){
            invert(l,r);
        }
        else{
            printf("%d\n",query(l,r));
        }
    }
    return 0;
}