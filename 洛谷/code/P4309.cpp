#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int tree[MAXN];

int head;
int cnt;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int key[MAXN];
double priority[MAXN];

int nums[MAXN];
int len;
int pos[MAXN];

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

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
}

int newnode(int val){
    ++cnt;
    sz[cnt]=1;
    key[cnt]=val;
    priority[cnt]=(double)rand()/RAND_MAX;
    return cnt;
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
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
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void inorder(int u){
    if(u){
        inorder(ls[u]);
        nums[++len]=key[u];
        inorder(rs[u]);
    }
}

inline int lowbit(int x){
    return x&-x;
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void update(int x,int v){
    while(x<=n){
        tree[x]=max(tree[x],v);
        x+=lowbit(x);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int pos=read();
        split(0,0,head,pos);
        int lm=rs[0];
        int r=ls[0];
        head=merge(merge(lm,newnode(i)),r);
    }
    inorder(head);
    for(int i=1;i<=n;i++){
        pos[nums[i]]=i;
        // cout<<nums[i]<<' ';
    }
    // cout<<endl;
    int lastans=0;
    for(int i=1;i<=n;i++){
        int ans=query(pos[i]);
        lastans=max(lastans,(ans+1));
        update(pos[i],ans+1);
        cout<<lastans<<endl;
    }
    return 0;
}