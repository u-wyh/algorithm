#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,q;
int val[MAXN];

int head=0;
int cnt=0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
int tag[MAXN];

int newnode(int val){
    ++cnt;
    key[cnt]=val;
    priority[cnt]=(double)rand()/RAND_MAX;
    sz[cnt]=1;
    return cnt;
}

void lazy(int i,int v){
    if(i){
        key[i]+=v;
        tag[i]+=v;
    }
}

void down(int i){
    if(i && tag[i]){
        lazy(ls[i],tag[i]);
        lazy(rs[i],tag[i]);
        tag[i]=0;
    }
}

void up(int i){
    if(i){
        sz[i]=sz[ls[i]]+sz[rs[i]]+1;
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
    down(l);
    down(r);
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

int getrank(int val, int head){
    int ans=0;
    int u=head;
    while(u){
        down(u);
        if(key[u]<val){
            ans+=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    return ans;
}

int get_kth_value(int tree, int k) {
    int u = tree;
    while (u) {
        down(u);
        if (sz[ls[u]] + 1 == k) {
            return key[u];
        } else if (sz[ls[u]] + 1 < k) {
            k -= sz[ls[u]] + 1;
            u = rs[u];
        } else {
            u = ls[u];
        }
    }
    return 0;
}

int main()
{
    srand(time(0));
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    for(int i=1;i<=n;i++){
        int rk=getrank(val[i],head);
        split(0,0,head,rk);
        int l=rs[0];
        int r=ls[0];
        head=merge(merge(l,newnode(val[i])),r);
    }
    for(int i=1;i<=q;i++){
        char op;
        int x,y;
        scanf(" %c %d %d",&op,&x,&y);
        if(op=='C'){
            int r1=getrank(y+1,head);
            int r2=getrank(x,head);
            printf("%d\n",r1-r2);
        }
        else{
            int h=y;
            int c=x;
            int rk=getrank(h,head);
            split(0,0,head,rk);
            int L=rs[0];
            int R=ls[0];
            if(R==0){
                head=merge(L,R);
                continue;
            }
            int c0=min(c,sz[R]);
            int v=get_kth_value(R,c0);
            int rk1=getrank(v,R);
            split(0,0,R,rk1);
            int B=rs[0];
            int CD=ls[0];
            int rk2=getrank(v+1,CD);
            split(0,0,CD,rk2);
            int C=rs[0];
            int D=ls[0];
            int k=c0-sz[B];
            split(0,0,C,k);
            int C1=rs[0];
            int C2=ls[0];
            lazy(B,1);
            lazy(C1,1);
            int CD_new=merge(C2,D);
            int BCD=merge(B,CD_new);
            int rk3=getrank(v+1,BCD);
            split(0,0,BCD,rk3);
            int Left=rs[0];
            int Right=ls[0];
            int BCD_new=merge(merge(Left,C1),Right);
            head=merge(L,BCD_new);
        }
    }
    return 0;
}