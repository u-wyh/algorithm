#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*10;
const int MAXV = 100;

int n,q;
int arr[MAXN];

int root[MAXV+1];
int ls[MAXT];
int rs[MAXT];
bool status[MAXT];

int pool[MAXT];
int top;

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

void prepare(){
    top=0;
    for(int i=1;i<MAXT;i++){
        pool[++top]=i;
    }
}

int newnode(){
    return pool[top--];
}

void del(int x){
    pool[++top]=x;
    ls[x]=0;
    rs[x]=0;
    status[x]=0;
}

void up(int i){
    status[i]=(status[ls[i]]|status[rs[i]]);
}

int insert(int pos,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=newnode();
    }
    if(l==r){
        status[rt]=true;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=insert(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(pos,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l, int r, int t1, int t2) {
	if (t1 == 0 || t2 == 0) {
		return t1 + t2;
	}
	if (l == r) {
		status[t1] |= status[t2];
	} else {
		int mid = (l + r) >> 1;
		ls[t1] = merge(l, mid, ls[t1], ls[t2]);
		rs[t1] = merge(mid + 1, r, rs[t1], rs[t2]);
		up(t1);
	}
	del(t2);
	return t1;
}

int tree1,tree2;

void split(int jobl,int jobr,int l,int r,int t1){
    if(t1==0){
        tree1=t1;
        tree2=0;
        return ;
    }
    if(jobl<=l&&r<=jobr){
        tree1=0;
        tree2=t1;
        return ;
    }
    int t2=newnode();
    int mid=(l+r)>>1;
    if(jobl<=mid){
        split(jobl,jobr,l,mid,ls[t1]);
        ls[t1]=tree1;
        ls[t2]=tree2;
    }
    if(jobr>mid){
        split(jobl,jobr,mid+1,r,rs[t1]);
        rs[t1]=tree1;
        rs[t2]=tree2;
    }
    up(t1);
    up(t2);
    tree1=t1;
    tree2=t2;
}

void compute(int val,int l,int r,int i){
    if(i==0||!status[i]){
        return ;
    }
    if(l==r){
        arr[l]=val;
    }
    else{
        int mid=(l+r)>>1;
        compute(val,l,mid,ls[i]);
        compute(val,mid+1,r,rs[i]);
    }
}

int main()
{
    prepare();
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<=n;i++){
        root[arr[i]]=insert(i,1,n,root[arr[i]]);
    }
    q=read();
    for(int i=1;i<=q;i++){
        int l,r,x,y;
        l=read(),r=read(),x=read(),y=read();
        split(l,r,1,n,root[x]);
        root[x]=tree1;
        root[y]=merge(1,n,root[y],tree2);
    }
    for(int i=1;i<=MAXV;i++){
        compute(i,1,n,root[i]);
    }
    for(int i=1;i<=n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}