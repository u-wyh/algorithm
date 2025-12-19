#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

int n,m;

int head=0;
int cnt=0;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
int addtag[MAXN];
bool rev[MAXN];
int val[MAXN];
int tree[MAXN];

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

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1; // 维护节点大小
    tree[i] = val[i];
    if (ls[i]) tree[i] = max(tree[i], tree[ls[i]]);
    if (rs[i]) tree[i] = max(tree[i], tree[rs[i]]);
}
void addlazy(int i,int v){
    if(i==0)
        return ;
    tree[i]+=v;
    val[i]+=v;
    addtag[i]+=v;
}

void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
    if(addtag[i]){
        addlazy(ls[i],addtag[i]);
        addlazy(rs[i],addtag[i]);
        addtag[i]=0;
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

int main()
{
    n=read(),m=read();
    for (int i = 1; i <= n; i++) {
        val[++cnt] = 0;
        sz[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        head = merge(head, cnt);
    }
    // cout<<head<<' '<<sz[head]<<endl;
    for(int i=1;i<=m;i++){
        int op,x,y,v;
        op=read(),x=read(),y=read();
        int lm,l,m,r;
        split(0,0,head,y);
        lm=rs[0];
        r=ls[0];
        split(0,0,lm,x-1);
        l=rs[0];
        m=ls[0];
        // cout<<l<<' '<<lm<<' '<<l<<' '<<r<<endl;
        if(op==1){
            v=read();
            addlazy(m,v);
        }
        else if(op==2){
            rev[m]^=1;
        }
        else{
            printf("%d\n",tree[m]);
        }
        head = merge(merge(l, m), r);
    }
    return 0;
}