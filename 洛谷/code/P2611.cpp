#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 4e4+5;

int row,col,n;
vector<int>vec[MAXM];

int head;
int cnt;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int val[MAXN];
int priority[MAXN];
long long all[MAXN];

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
    all[i]=all[ls[i]]+all[rs[i]]+1ll*(sz[ls[i]]+1)*(sz[rs[i]]+1)*val[i];
}

inline int newnode(int v){
    ++cnt;
    val[cnt]=v;
    priority[cnt]=v;
    sz[cnt]=1;
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

int build(int l,int r){
    if(l>r){
        return 0;
    }
    if(l==r){
        sz[l]=1;
        return l;
    }
    int mid=(l+r)>>1;
    sz[mid]=1;
    ls[mid]=build(l,mid-1);
    rs[mid]=build(mid+1,r);
    up(mid);
    return mid;
}

int main()
{
    row=read(),col=read(),n=read();
    for(int i=1;i<=n;i++){
        int x=read(),y=read();
        vec[x].push_back(y);
    }
    head=build(1,col);
    long long res=0;
    for(int i=1;i<=row;i++){
        for(int x:vec[i]){
            split(0,0,head,x);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            val[ls[0]]=priority[ls[0]]=i;
            head=merge(merge(rs[0],ls[0]),r);
        }
        res+=1ll*i*(col+1)*col/2-all[head];
    }
    res=1ll*row*(row+1)/2*col*(col+1)/2-res;
    cout<<res<<endl;
    return 0;
}